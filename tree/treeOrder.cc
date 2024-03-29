#include <stack>
#include <vector>

#include "treenode.h"

class TreeOrder {
public:
  std::vector<int> preOrderUnRecur(TreeNode *head) {
    std::vector<int> res;

    if (head == nullptr) {
      return res;
    }

    std::stack<TreeNode *> st;
    st.push(head);

    while (st.size()) {
      TreeNode *root = st.top();
      st.pop();

      res.push_back(root->val);

      if (root->right) {
        st.push(root->right);
      }
      if (root->left) {
        st.push(root->left);
      }
    }

    return res;
  }

  std::vector<int> inOrderUnRecur(TreeNode *head) {
    std::vector<int>       res;
    std::stack<TreeNode *> stack;

    if (head) {
      return res;
    }

    while (!stack.empty() || head != nullptr) {
      if (head != nullptr) {
        stack.push(head);
        head = head->left;  // 按照root，
                            // root->left的顺序压入栈，一直到root到最左叶子
      } else {
        head = stack.top();
        stack.pop();
        res.push_back(head->val);
        head = head->right;  // 开始遍历当前子树的右子树
      }
    }

    return res;
  }

  std::vector<int> postOrderUnRecu(TreeNode *head){
    std::vector<int> res;
    if(head == nullptr) {
      return res;
    }

    std::stack<TreeNode *> s1;
    std::stack<TreeNode *> s2;

    s1.push(head);

    while(s1.size()) {
      TreeNode *root = s1.top();
      s1.pop();
      s2.push(root);
      if(root->left) {
        s1.push(root->left);
      }

      if(root->right){
        s1.push(root->right);
      }
    }

    while(s2.size()) {
      res.push_back(s2.top()->val);
      s2.pop();
    }

    return res;
  }
};
