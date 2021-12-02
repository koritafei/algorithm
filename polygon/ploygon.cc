#include <math.h>
#include <stdio.h>

#define MAXN   1000
#define offset 10000
#define eps    1e-8

/**
 * @brief 判断当前传入数据是否为0
 *        将值于eps比较即可, 为0返回true，否则返回false
 * */
#define zero(x) (((x) > 0 ? (x) : (-x)) < eps)

/**
 * @brief 符号函数判断，> 0 == 1; == 0 ==0; < 0  == 2
 * */
#define _sign(x) ((x) > eps ? 1 : ((x) < -eps ? 2 : 0))

/**
 * @brief 点数据结构定义
 * */
struct point {
  double x, y;
};

/**
 * @brief 线数据结构定义
 * */
struct line {
  point a, b;
};

/**
 * @brief 叉积
 * @param  p1
 * @param  p2
 * @param  p0
 * @return double
 * */
double xmult(point p1, point p2, point p0) {
  return (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y);
}

/**
 * @brief 点积
 * @param  p1
 * @param  p2
 * @param  p0
 * @return double
 * */
double dmult(point p1, point p2, point p0) {
  return (p1.x - p0.x) * (p2.x - p0.x) + (p1.y - p0.y) * (p2.y - p0.y);
}

/**
 * @brief 判断凸多边形，顶点顺时针或逆时针给出, 允许共线
 *        根据定义，选中一条边其余边均在，这条边的同侧；
 *        即对每条边与临边的叉积的结果均大于0，或小于0，或==0(允许顶点共线)
 * @param  points
 * @param  n
 * @return int
 * */
int ConvexPolygon(int n, point *points) {
  int i, s[3] = {1, 1, 1};
  for (i = 0; i < n && s[1] | s[2]; i++) {
    s[_sign(xmult(points[(i + 1) % n], points[(i + 2) % n], points[i]))] = 0;
  }

  return s[1] | s[2];
}

/**
 * @brief 判断凸多边形，顶点顺时针或逆时针给出, 不允许共线
 *        根据定义，选中一条边其余边均在，这条边的同侧；
 *        即对每条边与临边的叉积的结果均大于0，或小于0，或==0(允许顶点共线)
 * @param  points
 * @param  n
 * @return int
 * */
int ConvexPolygon_2(int n, point *points) {
  int i, s[3] = {1, 1, 1};
  for (i = 0; i < n && s[0] && s[1] | s[2]; i++) {
    s[_sign(xmult(points[(i + 1) % n], points[(i + 2) % n], points[i]))] = 0;
  }

  return s[0] && s[1] | s[2];
}

/**
 * @brief 判断点在多边形内，允许点在多边形上。
 *        处理逻辑与凸多边形判断类似。判断点q与多边形的顶点构成的向量，
 *        与多边形边的向量的叉积，如果在多边形内或在多边形上，其叉积一定全部>0,或全部<0
 * @param  q
 * @param  n
 * @param  points
 * @return int
 * */
int insideConvex(point q, int n, point *points) {
  int i, s[3] = {1, 1, 1};
  for (i = 0; i < n && s[1] | s[2]; i++) {
    s[_sign(xmult(points[(i + 1) % n], q, points[i]))] = 0;
  }

  return s[1] | s[2];
}

/**
 * @brief 判断点在多边形内，不允许点在多边形上。
 *        处理逻辑与凸多边形判断类似。判断点q与多边形的顶点构成的向量，
 *        与多边形边的向量的叉积，如果在多边形内或在多边形上，其叉积一定全部>0,或全部<0
 * @param  q
 * @param  n
 * @param  points
 * @return int
 * */
int insideConvex_2(point q, int n, point *points) {
  int i, s[3] = {1, 1, 1};
  for (i = 0; i < n && s[0] && s[1] | s[2]; i++) {
    s[_sign(xmult(points[(i + 1) % n], q, points[i]))] = 0;
  }

  return s[0] && s[1] | s[2];
}

/**
 * @brief 判断点在任意多边形内，允许在多边形上.顶点顺时针或逆时针给出
 *        从目标点p出发引出一条射线，计算这条射线与多边形的交点个数
 *        如果在多边形内，其交点个数必为奇数，否在为偶数
 * @param  q
 * @param  n
 * @param  points
 * @param  on_edge 点是否在多边形上
 * @return int
 * */
int insidePlogon(point q, int n, point *points, int on_edge = 1) {
  point q2;  // 代表了无穷远处的一个顶点，与目标点p构成了一条射线。
  q2.x  = rand() + offset;
  q2.y  = rand() + offset;
  int i = 0, count = 0;

  while (i < n) {
    for (i = 0; i < n; i++) {
      if (zero(xmult(q, points[i], points[(i + 1) % n])) &&
          (points[i].x - q.x) * (points[(i + 1) % n].x - q.x) < eps &&
          (points[i].y - q.y) * (points[(i + 1) % n].y - q.y) < eps) {
        // 如果点在多边形上，其与顶点构成的向量中必定存在叉积为为0的情况，zero函数在为0是返回1
        // 在叉积为0的情况下需要判断，p是否在两个顶点构成的线段的延长线上，在延长线上点不会出现在
        // 多边形上，而是多边形外。
        // 判断p是否在线段内，只需判断q的坐标大于期中一个顶点的坐标，小于另一个顶点的坐标
        return on_edge;
      } else if (zero(xmult(q, q2, points[i]))) {
        // 当存在一个顶点在目标点为起始的线段上，说明p要么在多边形内，要么在多边形外
        // 此时可以终止循环判断
        break;
      } else if (xmult(q, points[i], q2) * xmult(q, points[(i + 1) % n], q2) <
                     -eps &&
                 xmult(points[i], q, points[(i + 1) % n]) *
                         xmult(points[i], q2, points[(i + 1) % n]) <
                     -eps) {
        // 判断射线与顶点构成的线段是否相交。
        count++;
      }
    }
  }

  return count & 1;
}

/**
 * @brief
 * 判断两条线段是否相交，如果两条直线相交，对应的端点与另一条线段的叉积的乘积一定小于0
 *        如果不想交，两者的叉积乘积一定大于0. 当两个线段共线叉积的乘积等于0
 * @param  l1
 * @param  l2
 * @param  p1
 * @param  p2
 * @return int
 * */
int oppositeSide(point l1, point l2, point p1, point p2) {
  return xmult(l1, p1, l2) * xmult(l1, p2, l2) < -eps;
}

/**
 * @brief 判断点是否在线段内，如果在线段内，点与线段端点的构成的向量，叉积==0
 *        同时该点的坐标在线段的端点坐标之间。
 * @param  l1
 * @param  l2
 * @param  p
 * @return int
 * */
int dotOnLineIn(point l1, point l2, point p) {
  return zero(xmult(l1, p, l2)) && (l1.x - p.x) * (l2.x - p.x) < eps &&
         (l1.y - p.y) * (l2.y - p.y) < eps;
}

/**
 * @brief 判断线段是否在多边形内
 * @param  l1
 * @param  l2
 * @param  n
 * @param  points
 * @return int
 * */
int insidePolygon(point l1, point l2, int n, point *points) {
  point t[MAXN], tt;
  int   i, j, k = 0;

  // 如果端点不在多边形内，那么线段一定不在多边形内
  if (!insidePlogon(l1, n, points) || !insidePlogon(l2, n, points)) {
    return 0;
  }

  for (int i = 0; i < n; i++) {
    // 如果线段和一条边相交返回0,内交
    if (oppositeSide(l1, l2, points[i], points[(i + 1) % n]) &&
        oppositeSide(points[i], points[(i + 1) % n], l1, l2)) {
      return 0;
    } else if (dotOnLineIn(l1, points[i], points[(i + 1) % n])) {
      t[k++] = l1;  // l1 在多边形边上
    } else if (dotOnLineIn(l2, points[i], points[(i + 1) % n])) {
      t[k++] = l2;  // l2 在多边形边上
    } else if (dotOnLineIn(points[i], l1, l2)) {
      t[k++] = points[i];  // 顶点在线段上
    }
  }

  for (i = 0; i < k; i++) {
    for (j = i + 1; j < k; j++) {
      tt.x = (t[i].x + t[j].x) / 2;  // 求两个交点的中点
      tt.y = (t[i].y + t[j].y) / 2;
      if (!insidePlogon(
              tt,
              n,
              points)) {  // 如果交点的中点不在多边形内，线段一定不在多边形内
        return 0;
      }
    }
  }

  return 1;
}

/**
 * @brief 求两条直线的交点
 * @param  u
 * @param  v
 * @return point
 * */
point intersection(line u, line v) {
  point  ret = u.a;
  double t =
      ((u.a.x - v.a.x) * (v.a.y - v.b.y) - (u.a.y - v.a.y) * (v.a.x - v.b.x)) /
      ((u.a.x - u.b.x) * (v.a.y - v.b.y) - (u.a.y - u.b.y) * (v.a.x - v.b.x));

  ret.x += (u.b.x - u.a.x) * t;
  ret.y += (u.b.y - u.b.y) * t;

  return ret;
}

/**
 * @brief 求三角形的重心
 *        三角形两条中线的交点，即为重心
 * @param  p1
 * @param  p2
 * @param  p3
 * @return point
 * */
point barycenter(point p1, point p2, point p3) {
  line u, v;
  u.a.x = (p1.x + p2.x) / 2;
  u.a.y = (p1.y + p2.y) / 2;
  u.b   = p3;

  v.a.x = (p1.x + p3.x) / 2;
  v.a.y = (p1.y + p3.y) / 2;
  v.b   = p2;

  return intersection(u, v);
}

/**
 * @brief 多边形重心
 * @param  n
 * @param  points
 * @return point
 * */
point barycenter(int n, point *points) {
  point  ret, t;
  double t1 = 0, t2;
  int    i;
  ret.x = ret.y = 0;

  for (int i = 1; i < n - 1; i++) {
    if (fabs(t2 = xmult(points[0], points[i], points[i + 1])) > eps) {
      t = barycenter(points[0], points[i], points[i + 1]);
      ret.x += t.x * t2;
      ret.y += t.y * t2;
      t1 += t2;
    }
  }

  if (fabs(t1) > eps) {
    ret.x /= t1;
    ret.y /= t1;
  }

  return ret;
}


