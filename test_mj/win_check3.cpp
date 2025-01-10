// dfs + 记忆化搜索

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

// 记忆化搜索存储
unordered_map<int, bool> memo;

// 将手牌转换为位表示
int convert_to_bits(const vector<int>& hand) {
  int bits = 0;
  for (int card : hand) {
    bits += 1 << ((card - 1) * 3);
  }
  return bits;
}

// 检查当前状态是否可以胡牌
bool canWin(int bits, bool hasPair) {
  if (bits == 0) return hasPair;  // 没有牌时，必须有一个对子才能胡牌
  if (memo.count(bits)) return memo[bits];

  // 尝试找对子
  if (!hasPair) {
    for (int i = 0; i < 9; ++i) {
      if (((bits >> (i * 3)) & 7) >= 2) {
        int new_bits = bits - (2 << (i * 3));
        if (canWin(new_bits, true)) {
          memo[bits] = true;
          return true;
        }
      }
    }
  }

  // 尝试找刻子
  for (int i = 0; i < 9; ++i) {
    if (((bits >> (i * 3)) & 7) >= 3) {
      int new_bits = bits - (3 << (i * 3));
      if (canWin(new_bits, hasPair)) {
        memo[bits] = true;
        return true;
      }
    }
  }

  // 尝试找顺子
  for (int i = 0; i < 7; ++i) {
    if (((bits >> (i * 3)) & 7) >= 1 && ((bits >> ((i + 1) * 3)) & 7) >= 1 &&
        ((bits >> ((i + 2) * 3)) & 7) >= 1) {
      int new_bits =
          bits - (1 << (i * 3)) - (1 << ((i + 1) * 3)) - (1 << ((i + 2) * 3));
      if (canWin(new_bits, hasPair)) {
        memo[bits] = true;
        return true;
      }
    }
  }

  memo[bits] = false;
  return false;
}

int main() {
  // 示例手牌（万子）
  vector<vector<int>> hands = {{1, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5},
                               {1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5},
                               {1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5}};

  for (const auto& hand : hands) {
    if (hand.size() != 14) {
      cout << "手牌数量错误，应该为14张。" << endl;
      continue;
    }
    int bits = convert_to_bits(hand);
    if (canWin(bits, false)) {
      cout << "可以胡牌" << endl;
    } else {
      cout << "不可以胡牌" << endl;
    }
  }

  return 0;
}
