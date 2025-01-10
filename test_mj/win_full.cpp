#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

unordered_map<string, bool> memo;

// 辅助函数：递归检查是否可以胡牌
bool canWinHelper(vector<int>& hand, bool hasPair) {
  string key = "";
  for (int count : hand) {
    key += to_string(count) + ",";
  }

  if (memo.find(key) != memo.end()) {
    return memo[key];
  }

  // 检查是否所有牌都被用完
  bool allZero = true;
  for (int count : hand) {
    if (count != 0) {
      allZero = false;
      break;
    }
  }
  if (allZero) {
    return hasPair;
  }

  // 尝试对子
  if (!hasPair) {
    for (int i = 0; i < 34; ++i) {
      if (hand[i] >= 2) {
        hand[i] -= 2;
        if (canWinHelper(hand, true)) {
          hand[i] += 2;
          memo[key] = true;
          return true;
        }
        hand[i] += 2;
      }
    }
  }

  // 尝试刻子
  for (int i = 0; i < 34; ++i) {
    if (hand[i] >= 3) {
      hand[i] -= 3;
      if (canWinHelper(hand, hasPair)) {
        hand[i] += 3;
        memo[key] = true;
        return true;
      }
      hand[i] += 3;
    }
  }

  // 尝试顺子（仅适用于万、筒、条）
  for (int i = 0; i < 27; ++i) {  // 只检查万、筒、条
    if (hand[i] > 0 && i % 9 <= 6) {
      if (hand[i + 1] > 0 && hand[i + 2] > 0) {
        hand[i]--;
        hand[i + 1]--;
        hand[i + 2]--;
        if (canWinHelper(hand, hasPair)) {
          hand[i]++;
          hand[i + 1]++;
          hand[i + 2]++;
          memo[key] = true;
          return true;
        }
        hand[i]++;
        hand[i + 1]++;
        hand[i + 2]++;
      }
    }
  }

  memo[key] = false;
  return false;
}

// 主函数：检查是否可以胡牌
bool canWin(vector<int> hand) {
  if (hand.size() != 14) {
    cout << "手牌数量错误，应该为14张。" << endl;
    return false;
  }

  // 合并所有花色和字牌
  vector<int> allTiles(34, 0);
  for (int tile : hand) {
    if (tile >= 1 && tile <= 9)
      allTiles[tile - 1]++;
    else if (tile >= 11 && tile <= 19)
      allTiles[tile - 2]++;
    else if (tile >= 21 && tile <= 29)
      allTiles[tile - 3]++;
    else if (tile >= 31 && tile <= 37)
      allTiles[tile - 4]++;
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
