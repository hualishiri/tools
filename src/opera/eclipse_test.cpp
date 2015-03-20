#include "opera/eclipse.h"

#include "util/testharness.h"
#include "util/tool.h"

namespace  tools {

void GetPoint(const Point2D& semi_major,
              const Point2D& semi_minor,
              float angle,
              double length,
              Point2D& point);

class ECLIPSE {};

TEST(ECLIPSE, GetLength) {
    for (int major_x = -5; major_x != 5; ++major_x) {
      for (int major_y = -5; major_y != 5; ++major_y) {
        for (int minor_x = -5; minor_x !=5; ++minor_x) {
          for (int minor_y = -5; minor_y != 5; ++minor_y) {
            for (int angle_i = -6; angle_i !=6; ++angle_i) {
              if ((major_x == 0 && major_y == 0) ||
                  (minor_x == 0 && minor_y == 0) ||
                  (DoubleEqual(minor_x, major_x) &&
                  DoubleEqual(minor_y, major_y)) ||
                  angle_i == 0)
                continue;
              Shape2D *eclipse = new Eclipse2D(Point2D(major_x, major_y), 
                  Point2D(minor_x, minor_y), angle_i);
              Point2D temp(0.0, 0.0);
              Point2D temp_std(0.0, 0.0);
              eclipse->GetPoint(fabs(angle_i), temp);
              Point2D major_temp(major_x, major_y);
              Point2D minor_temp(minor_x, minor_y);
              GetPoint(major_temp, minor_temp, angle_i, fabs(angle_i), temp_std);
              ASSERT_TRUE(DoubleEqual(temp.x, temp_std.x));
              ASSERT_TRUE(DoubleEqual(temp.y, temp_std.y));
              delete eclipse;
            }
          }
        }
      }
    } 
}

double Length(const Point2D& p) {
  return sqrt(pow(p.x, 2) + pow(p.y, 2));
}

double GetLength(const Point2D& semi_major,
                 const Point2D& semi_minor,
                 float angle) {
  //TODO: something
  double major = Length(semi_major);
  Point2D p(semi_minor.x - semi_major.x, semi_minor.y - semi_major.y);
  double minor = Length(p);
  return fabs(angle) * (major + minor) / 2;
}

double Angle(double x, double y) {
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

void GetPoint(const Point2D& semi_major,
              const Point2D& semi_minor,
              float angle,
              double length,
              Point2D& point) {
  if (DoubleEqual(length, 0.0)) {
    point.x = 0.0;
    point.y = 0.0;
    return;
  }
  double major = Length(semi_major);
  Point2D p(semi_minor.x - semi_major.x, semi_minor.y - semi_major.y);
  double minor = Length(p);
  float current_angle = length / (major + minor) * 2;
  double x = semi_major.x - major * cos(current_angle);
  double y = minor * sin(current_angle);
  double radius_temp = Length(Point2D(x, y));
  double angle_bise = Angle(x, y) + Angle(semi_major.x , semi_major.y);
  x = radius_temp * cos(angle_bise);
  y = radius_temp * sin(angle_bise);
  point.x = x;
  point.y = y;
}

} //namespace tools

int main(int argc, char** argv) {
  return tools::test::RunAllTests();
}
