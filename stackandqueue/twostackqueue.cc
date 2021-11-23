#include <iostream>
#include <stack>

template <typename T>
class TwoStackQueue {
public:
  T pop() {
    if (_stack2.empty()) {
      while (_stack1.size()) {
        _stack2.push(_stack1.top());
        _stack1.pop();
      }
    }

    if (!_stack2.empty()) {
      T top = _stack2.top();
      _stack2.pop();
      return top;
    }

    throw("queue is empty");
  }

  T top() {
    if (_stack2.empty()) {
      while (_stack1.size()) {
        _stack2.push(_stack1.top());
        _stack1.pop();
      }
    }

    if (!_stack2.empty()) {
      return _stack2.top();
    }

    throw("queue is empty");
  }

  void push(T val) {
    _stack1.push(val);
  }

private:
  std::stack<T> _stack1;
  std::stack<T> _stack2;
};

int main() {
  TwoStackQueue<int> s;
  s.push(1);
  s.push(2);
  s.push(3);
  std::cout << s.pop() << std::endl;
  std::cout << s.top() << std::endl;
  s.push(4);
  std::cout << s.pop() << std::endl;
  std::cout << s.pop() << std::endl;
  std::cout << s.pop() << std::endl;
}
