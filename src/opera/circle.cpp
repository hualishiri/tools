#include "opera/circle.h"

#include <assert.h>

#include "util/tool.h"

namespace tools {

//return the angle of the vecotr (x, y), range : [0, 2*PI]
double Circle2D::Angle(double x, double y) const {
  assert(!(DoubleEqual(x, 0.0) && DoubleEqual(y, 0.0)));
  if (DoubleEqual(x, 0.0) && y > 0.0)
    return T_PI / 2;
  if (DoubleEqual(x, 0.0) && y < 0.0)
    return 3*T_PI / 2;
  if (DoubleEqual(y, 0.0) && x > 0.0)
    return 0.0;
  if (DoubleEqual(y, 0.0) && x < 0.0)
    return T_PI;
  if (x > 0.0 && y > 0.0)
    return atan(y / x);
  if (x < 0.0 && y > 0.0)
    return T_PI + atan(y / x);
  if (x < 0.0 && y < 0.0 )
    return T_PI + atan(y / x);
  if (x > 0.0 && y < 0.0 )
    return 2 * T_PI + atan(y / x);
  return 0.0;
}

double Circle2D::Length(const Point2D& p) const {
  return sqrt(pow(p.x, 2) + pow(p.y, 2));
}

double Circle2D::GetLength() const {
  assert(angle_ < 2 * T_PI && angle_ > -2 * T_PI);
  return fabs(angle_) * radius_;
}

void Circle2D::GetPoint(double length, Point2D& point) const {
  assert((length > 0 && length < GetLength()) ||
      DoubleEqual(length, 0.0) ||
      DoubleEqual(length, GetLength()));
  if (DoubleEqual(length, 0.0)) {
    point.x = 0.0;
    point.y = 0.0;
    return;
  }
  float current_angle = length / radius_;
  double x = radius_ - radius_ * cos(current_angle);
  double y = radius_ * sin(current_angle);
  y = angle_ < 0 ? -y : y;
  double radius_temp = Length(Point2D(x, y));
  double angle_bise = Angle(x, y) + Angle(center_.x, center_.y);
  x = radius_temp * cos(angle_bise);
  y = radius_temp * sin(angle_bise);
  point.x = x;
  point.y = y;
}

} //namespace tools
