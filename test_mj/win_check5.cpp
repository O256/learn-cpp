// 胡牌算法5, 递归 + 剪枝

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// 辅助函数：递归检查是否可以胡牌
bool canWinHelper(vector<int>& hand, int start, bool hasPair) {
  int n = hand.size();
  if (start == n) {
    return hasPair;
  }

  // 剪枝：如果已经有对子，剩下的牌数必须是3的倍数
  if (hasPair && (n - start) % 3 != 0) {
    return false;
  }
  // 剪枝：如果还没有对子，剩下的牌数必须是3的倍数加2
  if (!hasPair && (n - start) % 3 == 1) {
    return false;
  }

  // 尝试对子
  if (!hasPair && start + 1 < n && hand[start] == hand[start + 1]) {
    if (canWinHelper(hand, start + 2, true)) {
      return true;
    }
  }

  // 尝试刻子
  if (start + 2 < n && hand[start] == hand[start + 1] &&
      hand[start] == hand[start + 2]) {
    if (canWinHelper(hand, start + 3, hasPair)) {
      return true;
    }
  }

  // 尝试顺子
  if (start + 2 < n) {
    int first = hand[start];
    int second = first + 1;
    int third = first + 2;
    auto it1 = find(hand.begin() + start, hand.end(), second);
    auto it2 = find(hand.begin() + start, hand.end(), third);
    if (it1 != hand.end() && it2 != hand.end()) {
      // 移除顺子中的牌
      hand.erase(it2);
      hand.erase(it1);
      if (canWinHelper(hand, start + 1, hasPair)) {
        return true;
      }
      // 恢复顺子中的牌
      hand.insert(it1, second);
      hand.insert(it2, third);
    }
  }

  return false;
}

// 主函数：检查是否可以胡牌
bool canWin(vector<int> hand) {
  if (hand.size() != 14) {
    cout << "手牌数量错误，应该为14张。" << endl;
    return false;
  }

  // 对手牌进行排序
  sort(hand.begin(), hand.end());

  return canWinHelper(hand, 0, false);
}

int main() {
  // 示例手牌（万子）
  vector<vector<int>> hands = {{1, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5},
                               {1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5},
                               {1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5}};

  for (auto hand : hands) {
    if (canWin(hand)) {
      cout << "可以胡牌" << endl;
    } else {
      cout << "不可以胡牌" << endl;
    }
  }

  return 0;
}
