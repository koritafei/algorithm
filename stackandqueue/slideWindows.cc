#include <list>
#include <vector>

#include "print.h"

std::vector<int> slideWindows(std::vector<int> &nums, int w) {
  std::list<int>   max;  // 存储slidewindows中最大值的index
  std::vector<int> res;

  for (int i = 0; i < nums.size(); i++) {
    // 当前元素大于队列中的元素时，弹出队列中的元素
    while (max.size() && nums[max.back()] < nums[i]) {
      max.pop_back();
    }
    max.push_back(i);

    // 需要先判断这一步，否则容易导致需要弹出的数据加入结果集
    // 当前队列中最大值索引为i-w,代表窗口已经越过front索引指向位置，需要弹出
    if (max.front() == i - w) {
      max.pop_front();
    }

    // 当i大于等于w-1时，max中索引大小一定在窗口中
    if (i >= w - 1) {
      res.push_back(nums[max.front()]);
    }
  }

  return res;
}

int main() {
  std::vector<int> nums = {4, 3, 5, 4, 3, 3, 6, 7};
  int              w    = 3;
  auto             res  = slideWindows(nums, w);
  print(res);
}
