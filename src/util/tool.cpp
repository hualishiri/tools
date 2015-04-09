#include "util/tool.h"

#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "map/map_projection.h"
#include "util/logger.h"

namespace tools {

extern const double T_PI = 3.14159265359;
extern const double kRadius = 6378137.0;

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

/* product a double number range from -1.0 ~ 1.0 */
double GetRandNumber(int seed) {
  srand(static_cast<unsigned>(time(NULL)) + seed);
  double number = rand() / (double)RAND_MAX;
  number *= 10000;
  number = number - static_cast<long long>(number);
  number = number * 10000000000.0;
  number = number / 10000000000.0;
  number = number * 2.0 - 1.0;
  return number;
}

double Radius(double angle) {
  return angle * T_PI / 180.0;
}

double Distance2D(double lhs_x, double lhs_y, double rhs_x, double rhs_y) {
  return sqrt(pow(lhs_x - rhs_x, 2.0) + pow(lhs_y - rhs_y, 2.0));
}

double Distance2DArc(double lhs_x, double lhs_y, double rhs_x, double rhs_y) {
  double wgs_lhs_x = lhs_x;
  double wgs_lhs_y = lhs_y;
  double wgs_rhs_x = rhs_x;
  double wgs_rhs_y = rhs_y;
  FromPixelToWgs(&wgs_lhs_x, &wgs_lhs_y);  
  FromPixelToWgs(&wgs_rhs_x, &wgs_rhs_y);  
  double longitude_range = Radius(wgs_rhs_x - wgs_lhs_x);
  double latitude_range = Radius(wgs_rhs_y - wgs_lhs_y);
  double a = pow(sin(latitude_range/2.0), 2.0)
      + cos(Radius(wgs_lhs_y)) * cos(Radius(wgs_rhs_y)) *
      pow(sin(longitude_range / 2.0), 2.0);
  double c = 2.0 * atan2(sqrt(a), sqrt(1.0-a));
  double d = kRadius * c;
  return d; 
}

} //namespace tools
