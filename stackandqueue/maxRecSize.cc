#include <iostream>
#include <stack>
#include <vector>

class Solution {
public:
  int maxRecSize(std::vector<std::vector<int>> &board) {
    std::vector<int> height = std::vector<int>(
        board[0].size(),
        0);  // 构建一个从低向上看的高度数组，如果底为0，在高度为0
    for (int i = 0; i < board.size(); i++) {
      for (int j = 0; j < board[i].size(); j++) {
        height[j] == (board[i][j] == 0 ? 0 : height[j] + 1);
      }
    }

    return maxArea(height);
  }

private:
  int maxArea(std::vector<int> &height) {
    std::stack<int> maxIndex;  // 存放从高到底的高度索引
    int             maxArea = 0;
    int             len     = height.size();
    for (int i = 0; i < len; i++) {
      while (maxIndex.size() && height[i] <= height[maxIndex.top()]) {
        // 如果当前元素小于等于栈顶元素，弹出栈顶元素，计算栈顶元素扩展的面积
        int j = maxIndex.top();
        maxIndex.pop();
        int k   = maxIndex.empty() ? -1 : maxIndex.top();
        maxArea = std::max(maxArea,
                           (i - k - 1) * height[j]);  // 面积为(i-k-1)*height[j]
      }
      maxIndex.push(i);
    }

    // 如果结束后栈非空
    while (maxIndex.size()) {
      int top = maxIndex.top();
      maxIndex.pop();
      int k = maxIndex.empty() ? -1 : maxIndex.top();
      // 对栈中存留的元素，其扩展方向一定到数组尾
      maxArea = std::max(maxArea, (len - k - 1) * height[top]);
    }

    return maxArea;
  }
};
