#include <iostream>
#include <vector>

#include "treenode.h"

class Edge {
public:
  void printEdge1(TreeNode *head) {
    if (head == nullptr) {
      return;
    }

    int height = getHeight(head, 0);

    std::vector<std::vector<TreeNode *>> edgeMap =
        std::vector<std::vector<TreeNode *>>(
            height + 1,
            std::vector<TreeNode *>(2, nullptr));
    setEdgeMap(head, 0, edgeMap);

    // 打印左节点
    for (int i = 0; i < height; i++) {
      std::cout << edgeMap[i][0]->val << ' ';
    }

    // 打印既不是左边界又不是右边界
    printLeafNotInMap(head, 0, edgeMap);

    // 打印右边界但不是左边界的节点
    for (int i = height - 1; i >= 0; i--) {
      if (edgeMap[i][0] != edgeMap[i][1]) {
        std::cout << edgeMap[i][1]->val << ' ';
      }
    }
  }

  void printEdge2(TreeNode *head) {
    if (head == nullptr) {
      return;
    }

    std::cout << head->val << ' ';

    if (head->left && head->right) {
      printLeftEdge(head->left, true);
      printRightEdge(head->right, true);
    } else {
      printEdge2(head->left == nullptr ? head->right : head->left);
    }
  }

private:
  int getHeight(TreeNode *root, int l) {
    if (root == nullptr) {
      return l;
    }

    return std::max(getHeight(root->left, l + 1),
                    getHeight(root->right, l + 1));
  }

  void setEdgeMap(TreeNode                             *root,
                  int                                   level,
                  std::vector<std::vector<TreeNode *>> &edgeMap) {
    // 处理每一层的最左和最右节点,
    // 根据定义edgeMap[level][0]为每一层的最左节点，也就是边界节点
    if (nullptr == root) {
      return;
    }

    edgeMap[level][0] = edgeMap[level][0] == nullptr ? root : edgeMap[level][0];
    edgeMap[level][1] = root;

    setEdgeMap(root->left, level + 1, edgeMap);
    setEdgeMap(root->right, level + 1, edgeMap);
  }

  void printLeafNotInMap(TreeNode                             *root,
                         int                                   level,
                         std::vector<std::vector<TreeNode *>> &edgeMap) {
    if (root == nullptr) {
      return;
    }

    if (root->left == nullptr && root->right == nullptr &&
        root != edgeMap[level][0] && root != edgeMap[level][1]) {
      std::cout << root->val << ' ';
    }

    printLeafNotInMap(root->left, level + 1, edgeMap);
    printLeafNotInMap(root->right, level + 1, edgeMap);
  }

  void printLeftEdge(TreeNode *root, bool print) {
    if (root == nullptr) {
      return;
    }

    if (print || root->left == nullptr || root->right == nullptr) {
      std::cout << root->val << ' ';
    }

    printLeftEdge(root->left, print);
    printLeftEdge(root->right, print && root->left == nullptr ? true : false);
  }

  void printRightEdge(TreeNode *root, bool print) {
    if (root == nullptr) {
      return;
    }

    printRightEdge(root->left, print && root->right == nullptr ? true : false);
    printRightEdge(root->right, print);

    if (print || (!root->left && !root->right)) {
      std::cout << root->val << ' ';
    }
  }
};
