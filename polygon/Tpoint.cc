#include <math.h>

#define eps     1e-8
#define zero(x) ((x) > 0 ? (x) : -(x)) < eps

struct point3 {
  double x, y, z;
};

struct line3 {
  point3 a, b, c;
};

struct plan3 {
  point3 a, b, c;
};

// 叉积计算
point3 xmult(point3 u, point3 v) {
  point3 ret;
  ret.x = u.y * v.x - v.y * u.z;
  ret.y = u.z * v.x - u.x * v.z;
  ret.z = u.x * v.y - u.y * v.x;

  return ret;
}

// 点积
double dmult(point3 u, point3 v) {
  return u.x * v.x + u.y * v.y + u.z * v.z;
}

// 矢量差
point3 subt(point3 u, point3 v) {
  point3 ret;
  ret.x = u.x - v.x;
  ret.y = u.y - v.y;
  ret.z = u.z - v.z;

  return ret;
}
