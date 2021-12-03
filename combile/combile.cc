#include <math.h>

#include <iostream>

#define MAXN 100
int count;

void dummy(int *a, int n) {
  std::cout << count++ << ":";
  for (int i = 0; i < n - 1; i++) {
    std::cout << a[i] << ' ';
  }
  std::cout << a[n - 1] << std::endl;
}

void _gen_perm(int *a, int n, int m, int l, int *tmp, int *tag) {
  int i = 0;
  if (l == m) {
    dummy(tmp, m);
  } else {
    for (i = 0; i < n; i++) {
      if (!tag[i]) {
        tmp[l] = a[i];
        tag[i] = l;
        _gen_perm(a, n, m, l + 1, tmp, tag);
        tag[i] = 0;
      }
    }
  }
}