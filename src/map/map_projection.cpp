#include "map/map_projection.h"

#include <cmath>
#include <algorithm>

namespace tools{
namespace{
double max(double x, double y){
  double temp = x;
  if(y > x) temp = y;
  return temp;
}

double min(double x, double y){
  double temp = x;
  if( y < x ) temp = y;
  return temp;
}
} //namespace

MapProjection* MapProjection::map_ = 0;

MapProjection* MapProjection::Instance(double zoom){
  if(!map_) map_ = new MapProjection(zoom);
  return map_;
}

MapProjection::MapProjection(double zoom)
  :zoom_(zoom),
  size_pixel_tile_(256),
  ratio_degree_to_radian_(180 / M_PI),
  ratio_radian_to_degree_( M_PI / 180 )
  {
  double pixel_global_size = size_pixel_tile_ * pow(2, zoom_);
  ratio_xpixel_to_degree_ = pixel_global_size / 360;
  ratio_ypixel_to_radian_ = pixel_global_size / ( 2 * M_PI );
  pixel_center_.x = pixel_global_size / 2;
  pixel_center_.y = pixel_global_size / 2;
}

void MapProjection::FromWgsToPixel(const WgsPoint& wgs_point,
    PixelPoint& pixel_point){
  pixel_point.x = round(pixel_center_.x 
    + wgs_point.longitude * ratio_xpixel_to_degree_); 
  double f = min(
      max(sin(wgs_point.latitude* ratio_radian_to_degree_),
        -0.9999), 0.9999);
  pixel_point.y = round(pixel_center_.y 
    + 0.5*log((1+f)/(1-f))* -ratio_ypixel_to_radian_);
}

void MapProjection::FromPixelToWgs(const PixelPoint& pixel_point,
    WgsPoint& wgs_point){
  wgs_point.longitude = (pixel_point.x - pixel_center_.x) 
    / ratio_xpixel_to_degree_;
  wgs_point.latitude = ( 2 * atan(exp((pixel_point.y - pixel_center_.y) 
    / - ratio_ypixel_to_radian_)) - M_PI / 2) * ratio_degree_to_radian_;
}

MapProjection& MapProjection::set_zoom(double zoom){
  zoom_ = zoom;
  double pixel_global_size = size_pixel_tile_ * pow(2, zoom_);
  ratio_xpixel_to_degree_ = pixel_global_size / 360;
  ratio_ypixel_to_radian_ = pixel_global_size / ( 2 * M_PI );
  pixel_center_.x = pixel_global_size / 2;
  pixel_center_.y = pixel_global_size / 2;
  return *this;
}

} //namespace tools
