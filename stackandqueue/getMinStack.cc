#include <iostream>
#include <stack>

template <typename T>
class MinStack {
public:
  T pop() {
    if (!_stack.empty()) {
      T val = _stack.top();
      _stack.pop();
      _minstack.pop();

      return val;
    }

    throw("stack is empty");
  }

  T getMin() {
    if (_minstack.size()) {
      return _minstack.top();
    }

    throw("stack is empty");
  }

  void push(T val) {
    _stack.push(val);

    if (_minstack.empty()) {
      _minstack.push(val);
    } else {
      T min = _minstack.top() > val ? val : _minstack.top();
      _minstack.push(min);
    }
  }

private:
  std::stack<T> _minstack;
  std::stack<T> _stack;
};

int main() {
  MinStack<int> s;
  s.push(1);
  s.push(2);

  std::cout << s.getMin() << std::endl;
  std::cout << s.pop() << std::endl;
  std::cout << s.getMin() << std::endl;
  std::cout << s.pop() << std::endl;
}