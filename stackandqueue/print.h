#ifndef __PRINT_H__
#define __PRINT_H__

#include <iostream>
#include <vector>

void print(std::vector<int> &nums) {
  for (auto item : nums) {
    std::cout << item << ' ';
  }

  std::cout << std::endl;
}

#endif /* __PRINT_H__ */
