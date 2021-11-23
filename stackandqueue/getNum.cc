#include <deque>
#include <vector>

class Solution {
public:
  int getNum(std::vector<int> &nums, int k) {
    std::deque<int> minstack;
    std::deque<int> maxstack;
    int             i   = 0;
    int             j   = 0;
    int             ans = 0;
    int             len = nums.size();

    while (i < len) {
      while (j < len) {
        // 求最大值与最小值索引
        while (minstack.size() && nums[j] <= nums[minstack.back()]) {
          minstack.pop_back();
        }
        minstack.push_back(j);  // 当前子数组中的最小值索引

        while (maxstack.size() && nums[j] >= nums[maxstack.back()]) {
          maxstack.pop_back();
        }
        maxstack.push_back(j);  // 当前子数组中最大值索引

        if (nums[maxstack.front()] - nums[minstack.front()] >
            k) {  // 最大值索引与最小值索引之差大于k，说明以满足条件
          break;
        }
        j++;
      }

      if (minstack.front() ==
          i) {  // 如果最小值索引等于i，表示子数组需要最左侧需要右移
        minstack.pop_front();
      }

      if (maxstack.front() == i) {
        maxstack.pop_front();
      }

      ans += j - i;
      i++;
    }

    return ans;
  }
};
