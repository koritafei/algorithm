#include <math.h>
#include <stdlib.h>

#define eps     1e-8
#define zero(x) ((x) > 0 ? (x) : -(x)) < eps

struct point {
  double x, y;
};

// 叉积
double xmult(point p1, point p2, point p0) {
  return (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y);
}

// graham顺时针查找包含所有共线点的凸包
point p1, p2;
int   grahamCp(const void *a, const void *b) {
  double ret = xmult(*((point *)a), *((point *)b), p1);

  return zero(ret) ? (xmult(*((point *)a), *((point *)b), p2) > 0 ? 1 : -1)
                     : (ret > 0 ? 1 : -1);
}

void _graham(int n, point *p, int &s, point *ch) {
  int i, k = 0;

  for (p1 = p2 = p[0], i = 1; i < n; p2.x += p[i].x, p2.y += p[i].y, i++) {
    if (p1.y - p[i].y > eps || (zero(p1.y - p[i].y) && p1.x > p[i].x)) {
      p1 = p[k = i];
    }
  }

  p2.x /= n;
  p2.y /= n;

  p[k] = p[0];
  p[0] = p1;
  qsort(p + 1, sizeof(point), grahamCp);

  for (ch[0] = p[0], ch[1] = p[1], ch[2] = p[2], s = i = 3; i < n;
       ch[s++] = p[i++]) {
    for (; s > 2 && xmult(ch[s - 2], p[i], ch[s - 1]) < -eps; s--)
      ;
  }
}
