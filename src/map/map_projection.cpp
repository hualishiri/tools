#include "map/map_projection.h"

#include <math.h>

#include <algorithm>

#include "util/tool.h"

namespace tools {
  
extern const double T_PI;

namespace {

double max(double x, double y) {
  double temp = x;
  if (y > x) temp = y;
  return temp;
}

double min(double x, double y) {
  double temp = x;
  if (y < x) temp = y;
  return temp;
}

} //namespace

MapProjection* MapProjection::Instance(double zoom) {
  if (!map_) map_ = new MapProjection(zoom);
  map_->set_zoom(zoom);
  return map_;
}


MapProjection& MapProjection::set_zoom(double zoom) {
  zoom_ = zoom;
  double pixel_global_size = kSizePixelTile* pow(2, zoom_);
  ratio_xpixel_to_degree_ = pixel_global_size / 360;
  ratio_ypixel_to_radian_ = pixel_global_size / (2 * T_PI);
  pixel_center_.x = pixel_global_size / 2;
  pixel_center_.y = pixel_global_size / 2;
  return *this;
}

void MapProjection::FromWgsToPixel(const WgsPoint& wgs_point,
                                   PixelPoint& pixel_point) {
  pixel_point.x = round(pixel_center_.x + wgs_point.longitude 
      * ratio_xpixel_to_degree_); 
  double f = min(max(sin(wgs_point.latitude * kRatioRadianToDegree),
                     -0.9999),
                 0.9999);
  pixel_point.y = round(pixel_center_.y + 0.5 * log((1 + f) 
      / (1 - f)) * -ratio_ypixel_to_radian_);
}

void MapProjection::FromPixelToWgs(const PixelPoint& pixel_point,
                                   WgsPoint& wgs_point) {
  wgs_point.longitude = (pixel_point.x - pixel_center_.x) 
      / ratio_xpixel_to_degree_;
  wgs_point.latitude = ( 2 * atan(exp((pixel_point.y - pixel_center_.y) 
      / - ratio_ypixel_to_radian_)) - T_PI / 2) *kRatioDegreeToRadian;
}

MapProjection::MapProjection(double zoom)
    : zoom_(zoom),
      kSizePixelTile(256),
      kRatioDegreeToRadian(180 / T_PI),
      kRatioRadianToDegree(T_PI / 180) {
  double pixel_global_size = kSizePixelTile* pow(2, zoom_);
  ratio_xpixel_to_degree_ = pixel_global_size / 360;
  ratio_ypixel_to_radian_ = pixel_global_size / (2 * T_PI);
  pixel_center_.x = pixel_global_size / 2;
  pixel_center_.y = pixel_global_size / 2;
}

MapProjection* MapProjection::map_ = 0;

} //namespace tools
