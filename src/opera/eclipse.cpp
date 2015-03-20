#include "opera/eclipse.h"

#include <assert.h>

#include "util/tool.h"

namespace tools {

extern const double T_PI;

double Eclipse2D::Length(const Point2D& p) const {
  return sqrt(pow(p.x, 2) + pow(p.y, 2));
}

double Eclipse2D::GetLength() const {
  //TODO: something
  double major = Length(semi_major_);
  Point2D p(semi_minor_.x - semi_major_.x, semi_minor_.y - semi_major_.y);
  double minor = Length(p);
  return fabs(angle_) * (major + minor) / 2;
}

void Eclipse2D::GetPoint(double length, Point2D& point) const {
  assert((length > 0 && length < GetLength()) ||
      DoubleEqual(length, 0.0) ||
      DoubleEqual(length, GetLength()));
  if (DoubleEqual(length, 0.0)) {
    point.x = 0.0;
    point.y = 0.0;
    return;
  }
  double major = Length(semi_major_);
  Point2D p(semi_minor_.x - semi_major_.x, semi_minor_.y - semi_major_.y);
  double minor = Length(p);
  float current_angle = length / (major + minor) * 2;
  double x = semi_major_.x - major * cos(current_angle);
  double y = minor * sin(current_angle);
  double radius_temp = Length(Point2D(x, y));
  double angle_bise = Angle(x, y) + Angle(semi_major_.x , semi_major_.y);
  x = radius_temp * cos(angle_bise);
  y = radius_temp * sin(angle_bise);
  point.x = x;
  point.y = y;
}

double Eclipse2D::Angle(double x, double y) const {
  assert(!(DoubleEqual(x, 0.0) && DoubleEqual(y, 0.0)));
  if (DoubleEqual(x, 0.0) && y > 0.0)
    return T_PI / 2;
  if (DoubleEqual(x, 0.0) && y < 0.0)
    return 3 * T_PI / 2;
  if (DoubleEqual(y, 0.0) && x > 0.0)
    return 0.0;
  if (DoubleEqual(y, 0.0) && x < 0.0)
    return T_PI;
  if (x > 0.0 && y > 0.0)
    return atan(y / x);
  if (x < 0.0 && y > 0.0)
    return T_PI + atan(y / x);
  if (x < 0.0 && y < 0.0)
    return T_PI + atan(y / x);
  if (x > 0.0 && y < 0.0)
    return 2 * T_PI + atan(y / x);
  return 0.0;
}

} //namespace tools
