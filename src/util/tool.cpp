#include "util/tool.h"

#include <assert.h>
#include <math.h>

#include "map/map_projection.h"

namespace tools {

extern const double T_PI = 3.14159265359;

namespace {
  
long long id = 0x0beef;

MapProjection::WgsPoint wgs_point;
MapProjection::PixelPoint pixel_point;

} //namespace

long long GenerateId() {
  ++id;
  return id;
}

void SetId(long long id_in) {
  id = id_in;
}

bool DoubleEqual(double lhs, double rhs) {
  if (lhs - rhs > -0.00000000001 && lhs - rhs < 0.0000000001)
    return true;
  return false;
}

double AngleInCircle(double x, double y) {
  assert(!(DoubleEqual(x, 0.0) && DoubleEqual(y, 0.0)));
  if (DoubleEqual(x, 0.0) && y > 0.0)
    return T_PI / 2;
  if (DoubleEqual(x, 0.0) && y < 0.0)
    return 3 * T_PI / 2;
  if (DoubleEqual(y, 0.0) && x > 0.0)
    return 0.0;
  if (DoubleEqual(y, 0.0 ) && x < 0.0)
    return T_PI;
  if ( x > 0.0 && y > 0.0 )
    return atan(y / x);
  if (x < 0.0 && y > 0.0)
    return T_PI + atan(y / x);
  if (x < 0.0 && y < 0.0 )
    return T_PI + atan(y / x);
  if(x > 0.0 && y < 0.0 )
    return 2 * T_PI + atan(y / x);
  return 0.0;
}

double AngleFromStartByClockInCircle(double start_x,
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
      select_angle = T_PI / 2.0;
    else
      select_angle = 3.0 * T_PI / 2.0;
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
  if (delta_angle < 0) delta_angle += 2 * T_PI;
  assert(delta_angle >= 0.0 && delta_angle <= 2 * T_PI);
  return delta_angle;
}

void FromWgsToPixel(double* longitude, double* latitude) {
  wgs_point.longitude = *longitude;
  wgs_point.latitude = *latitude;
  MapProjection::Instance(0)->FromWgsToPixel(wgs_point, pixel_point);
  *longitude = pixel_point.x;
  *latitude = pixel_point.y;
}

void FromPixelToWgs(double* x, double* y) {
  pixel_point.x = *x;
  pixel_point.y = *y;
  MapProjection::Instance(0)->FromPixelToWgs(pixel_point, wgs_point);
  *x = wgs_point.longitude;
  *y =wgs_point.latitude;
}

} //namespace tools
