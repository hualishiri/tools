#include "opera/circle.h"

#include "util/logger.h"
#include "util/testharness.h"
#include "util/tool.h"

namespace tools {

void GetPoint(const Point2D& circle,
              float angle,
              double length,
              Point2D& point);

class CIRCLE {};

TEST(CIRCLE, GetLength) {
  for (int i = -20; i != 20; ++i) {
    for (int j = -20; j != 20; ++j) {
      for (int k = -6; k <= 6; ++k) {
        if ((i == 0 && j == 0) || k == 0)
          continue;
        Shape2D* line = new Circle2D(Point2D(i, j), k);
        Point2D circle(i, j);
        Point2D temp_std(0.0, 0.0);

        Point2D temp(0.0, 0.0);
        line->GetPoint(std::abs(k), temp);

        GetPoint(circle, k, std::abs(k), temp_std);
        ASSERT_TRUE(DoubleEqual(temp.x, temp_std.x));
        ASSERT_TRUE(DoubleEqual(temp.y, temp_std.y));
        ASSERT_TRUE(DoubleEqual(line->GetLength(), std::abs(k) * sqrt(i * i + j * j)));   
        delete line;
        line = NULL;
      }
    }
  }
}

double Angle(double x, double y) {
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

double Length(const Point2D& p) {
  return sqrt(pow(p.x, 2) + pow(p.y, 2));
}

void GetPoint(const Point2D& circle,
              float angle,
              double length,
              Point2D& point) {
  if (DoubleEqual(length, 0.0)) {
    point.x = 0.0;
    point.y = 0.0;
    return;
  }
  double radius = Length(circle);
  float current_angle = length / radius;
  double x = radius - radius * cos(current_angle);
  double y = radius * sin(current_angle);
  y = angle < 0 ? -y : y;
  double radius_temp = Length(Point2D(x, y));
  double angle_bise = Angle(x, y) + Angle(circle.x, circle.y);
  x = radius_temp * cos(angle_bise);
  y = radius_temp * sin(angle_bise);
  point.x = x;
  point.y = y;
}

} //namespace tools

int main(int argc, char** argv) {
  return tools::test::RunAllTests();
}
