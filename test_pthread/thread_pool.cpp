#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <queue>

class ThreadPool {
public:
  ThreadPool(int numThreads, int maxTasks)
    : maxThreads_(numThreads),
    maxTasks_(maxTasks),
    activeThreads_(0),
    poolShutdown_(false)
  {
    for (int i = 0; i < numThreads; ++i) {
      threads_.emplace_back([this]() {
        while (true) {
          std::unique_lock lock(mutex_);
          condition_.wait(lock, [this]() {
            return poolShutdown_ || !tasks_.empty() || activeThreads_ < maxThreads_;
            });

          if (poolShutdown_) {
            lock.unlock();
            return;
          }

          ++activeThreads_;
          auto task = std::move(tasks_.front());
          tasks_.pop();
          lock.unlock();

          task();

          lock.lock();
          --activeThreads_;
          condition_.notify_one();
          lock.unlock();
        }
        });
    }
  }

  template<typename F, typename... Args>
  auto submit(F&& f, Args&&... args) -> std::future<decltype(f(args...))> {
    auto task = std::make_shared<std::packaged_task<decltype(f(args...))()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
    std::future<decltype(f(args...))> res = task->get_future();

    std::unique_lock lock(mutex_);
    condition_.wait(lock, [this]() {return poolShutdown_ || tasks_.size() < maxTasks_;});
    if (poolShutdown_) {
      throw std::runtime_error("submit on stopped ThreadPool");
    }

    tasks_.emplace([task]() {
      (*task)();
      });

    lock.unlock();
    condition_.notify_one();

    return res;
  }

  ~ThreadPool() {
    {
      std::unique_lock lock(mutex_);
      poolShutdown_ = true;
    }

    condition_.notify_all();

    for (auto& thread : threads_) {
      thread.join();
    }
  }

private:
  int maxThreads_;
  int maxTasks_;
  int activeThreads_;
  std::vector<std::thread> threads_;
  std::queue<std::function<void()>> tasks_;
  std::mutex mutex_;
  std::condition_variable condition_;
  bool poolShutdown_;
};

#include <iostream>
#include <chrono>

int main() {
  ThreadPool pool(4);
  auto future1 = pool.submit([]() { std::cout << "Task 1." << std::endl; return 1; });
  auto future2 = pool.submit([]() { std::cout << "Task 2." << std::endl; return 2; });
  std::cout << "Result 1: " << future1.get() << std::endl;
  std::cout << "Result 2: " << future2.get() << std::endl;

  // Submit more tasks before the previous ones finish:
  for (int i = 0; i < 8; ++i) {
    pool.submit([i]() { std::cout << "Task " << i + 1 << "." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000)); });
  }

  return 0;
}