#include <math.h>

const double pi = acos(-1);

// 计算圆心角lat表示纬度，-90 <= w <= 90,lng表示经度
// 返回两点所在的大圆劣弧所对应的圆心角, 0 <= andle <=pi
// 根据圆心角计算公式，首先求的纬度的差值，为消除误差采用 *pi/180的方式
// 因为要求的角度为锐角，所以需要判断差值与pi的关系，将dlng转化到0~pi的范围内
// 同样的对经度做误差校验，消除误差
// 利用反余弦求的夹角
double angle(double lng1, double lat1, double lng2, double lat2) {
  double dlng = fabs(lng1 - lng2) * pi / 180;
  while (dlng >= pi + pi) {
    dlng -= pi + pi;
  }
  if (dlng > pi) {
    dlng = pi + pi - dlng;
  }
  lat1 *= pi / 180;
  lat2 *= pi / 180;

  return acos(cos(lat1) * cos(lat2) * cos(dlng) + sin(lat1) * sin(lat2));
}

// 计算距离，r为球面半径
double distance(double r, double lng1, double lat1, double lng2, double lat2) {
  double dlng = fabs(lng1 - lng2) * pi / 180;

  if (dlng >= pi + pi) {
    dlng -= pi + pi;
  }

  if (dlng > pi) {
    dlng = pi + pi - dlng;
  }

  lat1 *= pi / 180;
  lat2 *= pi / 180;

  return r * sqrt(2 - 2 * (cos(lat1) * cos(lat2) * cos(dlng) +
                           sin(lat1) * sin(lat2)));
}

// 计算球面距离，r为球面半径
double sphereDist(double r,
                  double lng1,
                  double lat1,
                  double lng2,
                  double lat2) {
  return r * angle(lng1, lat1, lng2, lat2);
}