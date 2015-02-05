#include "map_projection.h"

#include <math.h>

#include "util/testharness.h"

namespace tools {

void FromWgsToPixel(int zoom,
                    const MapProjection::WgsPoint& wgs_point,
                    MapProjection::PixelPoint& pixel_point);
void FromPixelToWgs(int zoom,
                    const MapProjection::PixelPoint& pixel_point,
                    MapProjection::WgsPoint& wgs_point);

class MAPPROJECTION {};

TEST(MAPPROJECTION, FromWgsToPixel) {
  MapProjection::WgsPoint wgs_point;
  MapProjection::PixelPoint pixel_point;
  MapProjection::WgsPoint std_wgs_point;
  MapProjection::PixelPoint std_pixel_point;
  double data[][3] = {
    4, -87.6500522999, 41.850033920000003,
    5, -87.6500522999, 41.850033920000003,
    6, -87.6500522999, 41.850033920000003,
    7, -87.6500522999, 41.850033920000003,
    8, -87.6500522999, 41.850033920000003,
    9, -87.6500522999, 41.850033920000003,
    10, -95.231432143, 52.431243124312412
  };
  int array_size = sizeof(data) / sizeof(double) / 3;
  for(int i = 0; i != array_size; ++i) {
    wgs_point.longitude = data[i][1];
    wgs_point.latitude = data[i][2];
    MapProjection::Instance(data[i][0])->FromWgsToPixel(wgs_point, pixel_point);
    FromWgsToPixel(data[i][0], wgs_point, std_pixel_point);
    ASSERT_EQ(pixel_point.x, std_pixel_point.x);
    ASSERT_EQ(pixel_point.y, std_pixel_point.y);
  }
}

TEST(MAPPROJECTION, FromPixelToWgs) {
  MapProjection::WgsPoint wgs_point;
  MapProjection::PixelPoint pixel_point;
  MapProjection::WgsPoint std_wgs_point;
  MapProjection::PixelPoint std_pixel_point;
  double data[][3] = {
    1, 131, 190,
    4, 1050, 1522,
    5, 2101, 3045,
    6, 4202, 6091,
    7, 8405, 12182,
//  8, 16811, 24364,
    9, 33623, 48729
  };
  int array_size = sizeof(data) / sizeof(data[0][0]) / 3;
  for(int i = 0; i != array_size; ++i) {
    pixel_point.x = data[i][1];
    pixel_point.y = data[i][2];
    MapProjection::Instance(data[i][0])->FromPixelToWgs(pixel_point, wgs_point);
    FromPixelToWgs(data[i][0], pixel_point, std_wgs_point);
    ASSERT_EQ(wgs_point.longitude, std_wgs_point.longitude);
    ASSERT_EQ(wgs_point.latitude, std_wgs_point.latitude);
  }
}

double max(double x, double y) { return x > y ? x : y; }
double min(double x, double y) { return x > y ? y : x; }

namespace {

const double PI = 3.14159265359;
const double kSizePixelTile = 256.0;
const double kRatioDegreeToRadian = 180 / PI;
const double kRatioRadianToDegree = PI / 180;

} //namespace

void FromWgsToPixel(int zoom,
                    const MapProjection::WgsPoint& wgs_point,
                    MapProjection::PixelPoint& pixel_point) {
  double pixel_global_size = kSizePixelTile * pow(2, zoom);
  double ratio_xpixel_to_degree_ = pixel_global_size / 360;
  double ratio_ypixel_to_radian_ = pixel_global_size / (2 * PI);
  double pixel_center_x = pixel_global_size / 2;
  double pixel_center_y = pixel_global_size / 2; 
  pixel_point.x = round(pixel_center_x + wgs_point.longitude 
      * ratio_xpixel_to_degree_); 
  double f = min(max(sin(wgs_point.latitude * kRatioRadianToDegree),
                     -0.9999),
                 0.9999);
  pixel_point.y = round(pixel_center_y + 0.5 * log((1 + f) 
      / (1 - f)) * -ratio_ypixel_to_radian_);
}

void FromPixelToWgs(int zoom,
                    const MapProjection::PixelPoint& pixel_point,
                    MapProjection::WgsPoint& wgs_point) {
  double pixel_global_size = kSizePixelTile * pow(2, zoom);
  double ratio_xpixel_to_degree_ = pixel_global_size / 360;
  double ratio_ypixel_to_radian_ = pixel_global_size / (2 * PI);
  double pixel_center_x = pixel_global_size / 2;
  double pixel_center_y = pixel_global_size / 2; 
  wgs_point.longitude = (pixel_point.x - pixel_center_x) 
      / ratio_xpixel_to_degree_;
  wgs_point.latitude = ( 2 * atan(exp((pixel_point.y - pixel_center_y) 
      / - ratio_ypixel_to_radian_)) - PI / 2) *kRatioDegreeToRadian;
}

} //namespace tools

int main(int argc, char** argv) {
  return tools::test::RunAllTests();
}
