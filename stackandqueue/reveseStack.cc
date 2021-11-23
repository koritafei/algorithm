#include <iostream>
#include <stack>

class StackOp {
public:
  void reverseStack(std::stack<int> &stack) {
    if (stack.empty()) {
      return;
    } else {
      int i = getLastElemFromStack(stack);
      reverseStack(stack);
      stack.push(i);
    }
  }

private:
  int getLastElemFromStack(std::stack<int> &stack) {
    if (!stack.empty()) {
      int top = stack.top();
      stack.pop();
      if (stack.empty()) {
        return top;
      }

      int last = getLastElemFromStack(stack);
      stack.push(top);

      return last;
    }

    throw("stack is empty");
  }
};

int main() {
  std::stack<int> s;
  s.push(1);
  s.push(2);
  s.push(3);
  s.push(4);

  StackOp so;
  so.reverseStack(s);
  std::cout << s.top() << std::endl;
}
