// 胡牌算法2, 使用位运算 + DFS

#include <iostream>
#include <vector>
using namespace std;

// 递归函数，判断当前位表示的手牌是否可以胡牌
bool dfs(int bits, bool pair) {
  if (bits == 0) {
    return true;
  }
  if (pair) {
    // 找对子
    for (int i = 0; i < 9; ++i) { // 9种牌
      if ((bits >> (i * 3)) & 7 >= 2) { // 7是3进制表示的最大值
        int new_bits = bits - (2 << (i * 3));
        if (dfs(new_bits, false)) {
          return true;
        }
      }
    }
  } else {
    // 找顺子或刻子
    for (int i = 0; i < 9; ++i) {
      if ((bits >> (i * 3)) & 7 >= 3) {  // 刻子
        int new_bits = bits - (3 << (i * 3));
        if (dfs(new_bits, false)) {
          return true;
        }
      }
      if (i <= 6 && (bits >> (i * 3)) & 7 >= 1 &&
          (bits >> ((i + 1) * 3)) & 7 >= 1 &&
          (bits >> ((i + 2) * 3)) & 7 >= 1) {  // 顺子
        int new_bits =
            bits - (1 << (i * 3)) - (1 << ((i + 1) * 3)) - (1 << ((i + 2) * 3));
        if (dfs(new_bits, false)) {
          return true;
        }
      }
    }
  }
  return false;
}

// 判断手牌是否可以胡牌
bool can_hu(const vector<int>& hand) {
  int bits = 0;
  for (int card : hand) {
    bits += 1 << ((card - 1) * 3);   
  }
  return dfs(bits, true);
}

int main() {
  // 示例手牌 111万 222万 333万 444万 55万
  vector<int> hand = {1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5}; // 14张

  if (can_hu(hand)) {
    cout << "可以胡牌" << endl;
  } else {
    cout << "不可以胡牌" << endl;
  }

  return 0;
}
