#include <bitset>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <cstdint>

using namespace std;

unordered_map<uint64_t, bool> memo;

// 辅助函数：递归检查是否可以胡牌
bool canWinHelper(uint64_t hand, bool hasPair) {
  if (memo.find(hand) != memo.end()) {
    return memo[hand];
  }

  // 检查是否所有牌都被用完
  if (hand == 0) {
    return hasPair;
  }

  // 尝试对子
  if (!hasPair) {
    for (int i = 0; i < 34; ++i) {
      uint64_t mask = (uint64_t)3 << (i * 2);
      if ((hand & mask) >= (uint64_t)2 << (i * 2)) {
        if (canWinHelper(hand - ((uint64_t)2 << (i * 2)), true)) {
          memo[hand] = true;
          return true;
        }
      }
    }
  }

  // 尝试刻子
  for (int i = 0; i < 34; ++i) {
    uint64_t mask = (uint64_t)7 << (i * 2);
    if ((hand & mask) == (uint64_t)3 << (i * 2)) {
      if (canWinHelper(hand - ((uint64_t)3 << (i * 2)), hasPair)) {
        memo[hand] = true;
        return true;
      }
    }
  }

  // 尝试顺子（仅适用于万、筒、条）
  for (int i = 0; i < 27; ++i) {  // 只检查万、筒、条
    if (i % 9 <= 6) {
      uint64_t mask = ((uint64_t)1 << (i * 2)) |
                      ((uint64_t)1 << ((i + 1) * 2)) |
                      ((uint64_t)1 << ((i + 2) * 2));
      if ((hand & mask) == mask) {
        if (canWinHelper(hand - mask, hasPair)) {
          memo[hand] = true;
          return true;
        }
      }
    }
  }

  memo[hand] = false;
  return false;
}

// 主函数：检查是否可以胡牌
bool canWin(vector<int> hand) {
  if (hand.size() != 14) {
    cout << "手牌数量错误，应该为14张。" << endl;
    return false;
  }

  // 合并所有花色和字牌
  uint64_t allTiles = 0;
  for (int tile : hand) {
    if (tile >= 1 && tile <= 9)
      allTiles += (uint64_t)1 << ((tile - 1) * 2);
    else if (tile >= 11 && tile <= 19)
      allTiles += (uint64_t)1 << ((tile - 2) * 2);
    else if (tile >= 21 && tile <= 29)
      allTiles += (uint64_t)1 << ((tile - 3) * 2);
    else if (tile >= 31 && tile <= 37)
      allTiles += (uint64_t)1 << ((tile - 4) * 2);
  }

  // 初始化记忆化搜索的哈希表
  memo.clear();

  return canWinHelper(allTiles, false);
}

int main() {
  // 示例手牌（包含万、筒、条、字牌）
  vector<vector<int>> hands = {
      {1, 2, 1, 11, 11, 11, 21, 21, 21, 31, 31, 31, 32, 32},
      {1, 2, 3, 11, 12, 13, 21, 22, 23, 31, 31, 31, 32, 32},
      {1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5}};

  for (auto hand : hands) {
    if (canWin(hand)) {
      cout << "可以胡牌" << endl;
    } else {
      cout << "不可以胡牌" << endl;
    }
  }

  return 0;
}
