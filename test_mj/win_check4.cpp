// 动态规划

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// 辅助函数：检查是否可以胡牌
bool canWin(const vector<int>& hand) {
  if (hand.size() != 14) {
    cout << "手牌数量错误，应该为14张。" << endl;
    return false;
  }

  // 对手牌进行排序
  vector<int> sorted_hand = hand;
  sort(sorted_hand.begin(), sorted_hand.end());

  // 初始化dp数组
  vector<vector<vector<bool>>> dp(
      15, vector<vector<bool>>(5, vector<bool>(2, false)));
  dp[0][0][0] = true;

  // 遍历每一张牌
  for (int i = 0; i < 14; ++i) {
    for (int j = 0; j <= 4; ++j) {   // 最多有4个刻子/顺子
      for (int k = 0; k < 2; ++k) {  // 是否已经有一个对子
        if (!dp[i][j][k]) continue;

        // 尝试将当前牌作为对子
        if (k == 0 && i + 1 < 14 && sorted_hand[i] == sorted_hand[i + 1]) {
          dp[i + 2][j][1] = true;
        }

        // 尝试将当前牌作为刻子
        if (i + 2 < 14 && sorted_hand[i] == sorted_hand[i + 1] &&
            sorted_hand[i] == sorted_hand[i + 2]) {
          dp[i + 3][j + 1][k] = true;
        }

        // 尝试将当前牌作为顺子
        if (i + 2 < 14 && sorted_hand[i] + 1 == sorted_hand[i + 1] &&
            sorted_hand[i] + 2 == sorted_hand[i + 2]) {
          dp[i + 3][j + 1][k] = true;
        }
      }
    }
  }

  // 检查是否可以胡牌
  return dp[14][4][1];
}

int main() {
  // 示例手牌（万子）
  vector<vector<int>> hands = {{1, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5},
                               {1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5},
                               {1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5}};

  for (const auto& hand : hands) {
    if (canWin(hand)) {
      cout << "可以胡牌" << endl;
    } else {
      cout << "不可以胡牌" << endl;
    }
  }

  return 0;
}
