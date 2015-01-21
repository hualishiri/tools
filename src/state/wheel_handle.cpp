#include "state/wheel_handle.h"

#include "map/map.h"
#include "map/map_projection.h"

namespace tools{

void WheelHandle::Initialize() {
  int delta = angle_ / 120;
  int new_zoom = Map::Instance()->zoom() + delta;
  if (new_zoom < 4 || new_zoom > 20) new_zoom -= delta;

  MapProjection::PixelPoint pixel_point;
  MapProjection::WgsPoint wgs_point;
  pixel_point.x = Map::Instance()->origin_x() + x_;
  pixel_point.y = Map::Instance()->origin_y() + y_;
  MapProjection::Instance(Map::Instance()->zoom())
      ->FromPixelToWgs(pixel_point, wgs_point);

  MapProjection::Instance(new_zoom)->FromWgsToPixel(wgs_point, pixel_point);

  map_zoom_ = new_zoom;
  map_origin_x_ = pixel_point.x - x_;
  map_origin_y_ = pixel_point.y - y_;
  pixel_point.x = map_origin_x_ + Map::Instance()->width() / 2;
  pixel_point.y = map_origin_y_ + Map::Instance()->height() / 2;
  MapProjection::Instance(new_zoom)->FromPixelToWgs(pixel_point, wgs_point);
  map_center_longitude_ = wgs_point.longitude;
  map_center_latitude_ = wgs_point.latitude;
  init_ = true;
}

} //namespace tools
