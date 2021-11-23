
#include <iostream>
#include <stack>

void stackSort(std::stack<int> &st) {
  std::stack<int> helper;
  while (st.size()) {
    int top = st.top();
    st.pop();

    while (!helper.empty() && helper.top() < top) {
      st.push(helper.top());
      helper.pop();
    }

    helper.push(top);
  }

  while (helper.size()) {
    st.push(helper.top());
    helper.pop();
  }
}

int main() {
  std::stack<int> s;
  s.push(1);
  s.push(3);
  s.push(2);
  s.push(10);

  stackSort(s);

  while (s.size()) {
    std::cout << s.top() << ' ';
    s.pop();
  }
  std::cout << '\n';
}
