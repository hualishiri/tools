#include "opera/opera_option.h"

#include "map/map_projection.h"
#include "util/logger.h"

namespace tools {
namespace {

MapProjection::WgsPoint wgs_point;
MapProjection::PixelPoint pixel_point;

void FromWgsToPixel(double* longitude, double* latitude) {
  wgs_point.longitude = *longitude;
  wgs_point.latitude = *latitude;
  MapProjection::Instance(0)->FromWgsToPixel(wgs_point, pixel_point);
  *longitude = pixel_point.x;
  *latitude = pixel_point.y;
}

} //namespace

OperaOption* OperaOption::opera_option_ = 0;

OperaOption* OperaOption::Instance() {
  if (opera_option_ == 0)
    opera_option_ = new OperaOption();
  return opera_option_;
}

void OperaOption::pop_radar(long long id) {
  std::vector<Radar>::iterator iter = radars_.begin();
  for (; iter != radars_.end(); ++iter) {
    if (iter->id == id) {
      radars_.erase(iter);
      return;
    }
  }
}

void OperaOption::pop_object(long long id) {
  std::vector<Object>::iterator iter = objects_.begin();
  for (; iter != objects_.end(); ++iter) {
    if (iter->id == id) {
      objects_.erase(iter);
      return;
    }
  }
}

void OperaOption::ConvertToPixel() {
  for (std::size_t i=0; i!=radars_.size(); ++i) {
    FromWgsToPixel(&radars_[i].start_x, &radars_[i].start_y);
    FromWgsToPixel(&radars_[i].radius_x, &radars_[i].radius_y);
  }  
  for (std::size_t i=0; i!=tracks_.size(); ++i) {
    for (std::size_t j=0; j!=tracks_[i].lines.size(); ++j) {
      LogInfo("Before Convert: (%f, %f)",
              tracks_[i].lines[j].start_x,
              tracks_[i].lines[j].start_y);
      FromWgsToPixel(&tracks_[i].lines[j].start_x, &tracks_[i].lines[j].start_y);
      FromWgsToPixel(&tracks_[i].lines[j].end_x, &tracks_[i].lines[j].end_y);
      LogInfo("After Convert: (%f, %f)",
              tracks_[i].lines[j].start_x,
              tracks_[i].lines[j].start_y);
    }
    for (std::size_t j=0; j!=tracks_[i].circles.size(); ++j) {
      FromWgsToPixel(&tracks_[i].circles[j].start_x, &tracks_[i].circles[j].start_y);
      FromWgsToPixel(&tracks_[i].circles[j].center_x, &tracks_[i].circles[j].center_y);
      FromWgsToPixel(&tracks_[i].circles[j].side_x, &tracks_[i].circles[j].side_y);
      FromWgsToPixel(&tracks_[i].circles[j].angle_x, &tracks_[i].circles[j].angle_y);
    }
    for (std::size_t j=0; j!=tracks_[i].eclipses.size(); ++j) {
      FromWgsToPixel(&tracks_[i].eclipses[j].start_x, &tracks_[i].eclipses[j].start_y);
      FromWgsToPixel(&tracks_[i].eclipses[j].center_x, &tracks_[i].eclipses[j].center_y);
      FromWgsToPixel(&tracks_[i].eclipses[j].side_x, &tracks_[i].eclipses[j].side_y);
      FromWgsToPixel(&tracks_[i].eclipses[j].end_x, &tracks_[i].eclipses[j].end_y);
      FromWgsToPixel(&tracks_[i].eclipses[j].angle_x, &tracks_[i].eclipses[j].angle_y);
    }
  }
}

} //namespace tools
