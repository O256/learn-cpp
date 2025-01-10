#include <algorithm>
#include <iostream>
#include <vector>

// 判断是否是顺子
bool isSequence(const std::vector<int>& hand, int start) {
  return hand[start] > 0 && hand[start + 1] > 0 && hand[start + 2] > 0;
}

// 判断是否是刻子
bool isTriplet(const std::vector<int>& hand, int start) {
  return hand[start] >= 3;
}

// 递归判断是否可以胡牌
bool canWin(std::vector<int>& hand, int pairs) {
  // 如果所有牌都被处理完了并且已经有一对将牌，返回 true
  if (std::all_of(hand.begin(), hand.end(), [](int x) { return x == 0; }) &&
      pairs == 1) {
    return true;
  }

  // 遍历手牌
  for (int i = 0; i < hand.size(); ++i) {
    if (hand[i] == 0) continue;  // 跳过空牌

    // 尝试将当前牌作为将牌
    if (pairs == 0 && hand[i] >= 2) {
      hand[i] -= 2;
      if (canWin(hand, pairs + 1)) return true;
      hand[i] += 2;  // 回溯
    }

    // 尝试将当前牌作为顺子的一部分
    if (i <= hand.size() - 3 && isSequence(hand, i)) {
      hand[i]--; 
      hand[i + 1]--;
      hand[i + 2]--;
      if (canWin(hand, pairs)) return true;
      hand[i]++;
      hand[i + 1]++;
      hand[i + 2]++;  // 回溯
    }

    // 尝试将当前牌作为刻子的一部分
    if (isTriplet(hand, i)) {
      hand[i] -= 3;
      if (canWin(hand, pairs)) return true;
      hand[i] += 3;  // 回溯
    }

    break;  // 如果当前牌无法作为将牌、顺子或刻子的一部分，则不可能胡牌
  }

  return false;
}

bool isWinningHand(std::vector<int>& hand) { return canWin(hand, 0); }

int main() {
  // 手牌示例：1, 2, 3 万，4, 5, 6 万，7, 8, 9 万，1, 1, 1 筒，2, 2 筒
  std::vector<int> hand = {
      1, 1, 1,  // 1-3 万
      1, 1, 1,  // 4-6 万
      1, 1, 1,  // 7-9 万
      3, 0, 0,  // 1 筒
      2, 0, 0,  // 2 筒
      0, 0, 0,  // 3 筒
      0, 0, 0,  // 4 筒
      0, 0, 0,  // 5 筒
      0, 0, 0,  // 6 筒
      0, 0, 0,  // 7 筒
      0, 0, 0,  // 8 筒
      0, 0, 0,  // 9 筒
      0, 0, 0,  // 东
      0, 0, 0,  // 南
      0, 0, 0,  // 西
      0, 0, 0,  // 北
      0, 0, 0,  // 中
      0, 0, 0,  // 发
      0, 0, 0   // 白
  };

  if (isWinningHand(hand)) {
    std::cout << "胡牌!" << std::endl;
  } else {
    std::cout << "不能胡牌" << std::endl;
  }

  return 0;
}
