// 多边形切割

#include <math.h>
#include <stdio.h>

#define MAXN 100
#define eps  1e-8

#define zero(x) (((x) > 0 ? (x) : -(x)) < eps)

struct point {
  double x, y;
};

// 叉积
double xmult(point p1, point p2, point p0) {
  return (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p2.y - p0.y);
}

// 判断线段是否不相交
int sameSide(point p1, point p2, point l1, point l2) {
  return xmult(l1, p1, l2) * xmult(l1, p2, l2) > eps;
}

// 计算线段的交点
point intersection(point p1, point p2, point l1, point l2) {
  point  ret = p1;
  double t   = ((p1.x - l1.x) * (l1.y - l2.y) - (p1.y - p2.y) * (l1.x - l2.x)) /
             ((p1.x - p2.x) * (l2.y - l1.y) - (p1.y - p2.y) * (l1.x - l2.x));

  ret.x += (p2.x - p1.x) * t;
  ret.y += (p2.y - p1.y) * t;
  return ret;
}

/**
 * @brief  多边形沿l1l2,在silde侧切割
 * @param  n
 * @param  p
 * @param  l1
 * @param  l2
 * @param  silde
 * */
void ploygonCut(int &n, point *p, point l1, point l2, point silde) {
  point pp[100];
  int   m = 0, i;

  for (i = 0; i < n; i++) {
    // 如果p[i]silde构成的直线与l1l2不相交，直接加入到pp中
    if (sameSide(p[i], silde, l1, l2)) {
      pp[m++] = p[i];
    }

    // 临边与l1l2相交的情况，加入其交点
    if (!sameSide(p[i], p[(i + 1) % n], l1, l2) &&
        !(zero(xmult(p[i], l1, l2))) && (zero(xmult(p[(i + 1) % n], l1, l2)))) {
      pp[m++] = intersection(p[i], p[(i + 1) % n], l1, l2);
    }
  }

  // 去除坐标重叠的部分，
  for (n = i = 0; i < m; i++) {
    if (!i || !zero(pp[i].x - pp[i - 1].x) || !zero(pp[i].y - pp[i - 1].y)) {
      p[n++] = pp[i];
    }
  }

  // 判断首位端点是否相同，如果相同则丢弃
  if (zero(p[n - 1].x - p[0].x) && zero(p[n - 1].y - p[0].y)) {
    n--;
  }

  // 不构成多边形
  if (n < 3) {
    n = 0;
  }
}