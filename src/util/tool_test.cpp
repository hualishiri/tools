#include "util/tool.h"

#include <math.h>

#include <iostream>

#include "util/testharness.h"

namespace tools {
namespace {

const double PI = 3.14159265359;

} //namespace

double StdAngleInCircle(double x, double y);
double StdAngleFromStartByClockInCircle(double start_x,
                                        double start_y,
                                        double center_x,
                                        double center_y,
                                        double angle_x,
                                        double angle_y);

class Empty {};

TEST(Empty, GenerateId) {
  const long long start_id = 0x0bef0;
  for(int i = 0; i != 100; ++i)
    ASSERT_EQ(GenerateId(), start_id + i);
}

TEST(Empty, SetId) {
  for( int i = 0; i != 100; ++i ) {
    SetId(i);
    ASSERT_EQ(GenerateId(), i + 1);
  }
}

TEST(Empty, DoubleEqual) {
  ASSERT_TRUE(!DoubleEqual(0.1, 0.2));
  ASSERT_TRUE(DoubleEqual(0.131432345321341, 0.131432345321982));
}

TEST(Empty, AngleInCircle) {
  for (int i = -100; i != 100; ++i) {
    for (int j = -100; j != 100; ++j) {
      if ( i == 0 && j == 0 ) continue;
      ASSERT_EQ(StdAngleInCircle(i, j), AngleInCircle(i, j));
    }
  }
}

TEST(Empty, AngleFromStartByClockInCircle) {
  /*for (int i = -10; i != 10; ++i) {
    for (int j = -10; j != 10; ++j) {
      for (int k = -10; k != 10; ++k) {
        for (int l = -10; l != 10; ++l) {
          for (int m = -10; m != 10; ++m) {
            for (int n = -10; n != 10; ++n) {
              if ( i == k && j == l || i == m && j == n || k == m && l == n )
                continue;
              ASSERT_EQ(AngleFromStartByClockInCircle(i, j, k, l, m, n),
                        StdAngleFromStartByClockInCircle(i, j, k, l, m, n));
            }
          }
        }
      }
    }
  }*/
}

double StdAngleInCircle(double x, double y) {
  if (DoubleEqual(x, 0.0) && y > 0.0)
    return PI / 2;
  if (DoubleEqual(x, 0.0) && y < 0.0)
    return 3 * PI / 2;
  if (DoubleEqual(y, 0.0) && x > 0.0)
    return 0.0;
  if (DoubleEqual(y, 0.0 ) && x < 0.0)
    return PI;
  if ( x > 0.0 && y > 0.0 )
    return atan(y / x);
  if (x < 0.0 && y > 0.0)
    return PI + atan(y / x);
  if (x < 0.0 && y < 0.0 )
    return PI + atan(y / x);
  if(x > 0.0 && y < 0.0 )
    return 2 * PI + atan(y / x);
  return 0.0;
}

double StdAngleFromStartByClockInCircle(double start_x,
                                        double start_y,
                                        double center_x,
                                        double center_y,
                                        double angle_x,
                                        double angle_y) {
  double a = center_x;
  double b = center_y;
  double r_square = pow(center_y - start_y, 2) + pow(center_x - start_x, 2); 
  double select_angle = 0;
  if (DoubleEqual(angle_x, center_x)) {
    double y1 = b + sqrt(a * a + r_square);
    double y2 = b - sqrt(a * a + r_square);
    if (fabs(y1 - angle_y) > fabs(y2 - angle_y)) y1 = y2;
    if (y1 - center_y > 0)
      select_angle = PI / 2.0;
    else
      select_angle = 3.0 * PI / 2.0;
  } else {
    double c = angle_y - ((angle_y - center_y) 
        / (angle_x - center_x)) * angle_x;
    double k = (angle_y - center_y) / (angle_x - center_x);
    double l = 1 + k * k;
    double m = 2 * (c * k - a - b * k);
    double n = a * a + (c - b) * (c - b) - r_square;
    double x1 = (-m + sqrt(m * m - 4 * n * l)) / 2 / l;
    double y1 = k * x1 + c;
    double x2 = (-m - sqrt(m * m - 4 * n * l)) / 2 / l;
    double y2 = k * x2 + c;
    if (fabs(angle_x - x1) > fabs(angle_x - x2)) {
      x1 = x2;
      y1 = y2;
    }
    select_angle = AngleInCircle(x1 - center_x, y1 - center_y);
  }
  double start_angle = AngleInCircle(start_x - center_x, start_y - center_y);
  double delta_angle = start_angle - select_angle;
  if (delta_angle < 0) delta_angle += 2 * PI;
  return delta_angle;
}

} //namespace tools

int main(int argc, char** argv) {
  return tools::test::RunAllTests();
}
