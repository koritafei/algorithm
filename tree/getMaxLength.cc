/**
 * ]@Copyright (c) 2021  koritafei
 * @file getMaxLength.cc
 * @brief
 * @author koritafei (koritafei@gmail.com)
 * @version 0.1
 * @date 2021-11-24 13:11:51
 *
 * */

#include <iostream>
#include <map>

#include "treenode.h"

class PartSumMaxLength {
public:
  int getMaxLength(TreeNode *root, int sum) {
    std::map<int, int> sumMap;
    sumMap.insert(0, 0);

    return preOrderSumLength(root, sum, 0, 1, 0, sumMap);
  }

private:
  int preOrderSumLength(TreeNode           *root,
                        int                 sum,
                        int                 presum,
                        int                 level,
                        int                 maxLen,
                        std::map<int, int> &sumMap) {
    if (nullptr == root) {
      return maxLen;
    }

    // 做选择
    int cursum = presum + root->val;

    // 是否已经存在，不存在更新
    if (!sumMap.count(cursum)) {
      sumMap.insert(cursum, level);
    }

    // 最值判断，需要比较，cursum是否为sum,
    // 当cursum == sum 时，cursum - sum == 0, 此时当前的最大深度为level
    // 如果cursum != sum 时，
    // 且sumMap中不存在cursum-sum时，其最大深度一定在下一层
    // 如果存在值，代表从存在路径从非root，开始，其和为sum
    if (sumMap.count(cursum - sum)) {
      maxLen = std::max(maxLen, level - sumMap[cursum - sum]);
    }

    // 递归左右分支
    maxLen =
        preOrderSumLength(root->left, sum, cursum, level + 1, maxLen, sumMap);
    maxLen =
        preOrderSumLength(root->right, sum, cursum, level + 1, maxLen, sumMap);

    // 撤销选择，此处撤销选择时，需要判断，当前值是否为此次操作加入的
    if (level == sumMap[cursum]) {
      sumMap.erase(cursum);
    }

    return maxLen;
  }
};
