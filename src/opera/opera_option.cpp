#include "opera/opera_option.h"

#include "map/map_projection.h"

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

void OperaOption::push_back_radar(Radar& radar) {
  FromWgsToPixel(&radar.start_x, &radar.start_y);
  FromWgsToPixel(&radar.radius_x, &radar.radius_y);
  radars_.push_back(radar);
}

void OperaOption::push_back_object(Object& object) {
  FromWgsToPixel(&object.x, &object.y);
  objects_.push_back(object);
}

void OperaOption::push_back_track(Track& track) {
  for (std::size_t i=0; i!=track.lines.size(); ++i) {
    FromWgsToPixel(&track.lines[i].start_x, &track.lines[i].start_y);
    FromWgsToPixel(&track.lines[i].end_x, &track.lines[i].end_y);
  }
  for (std::size_t i=0; i!=track.circles.size(); ++i) {
    FromWgsToPixel(&track.circles[i].start_x, &track.circles[i].start_y);
    FromWgsToPixel(&track.circles[i].center_x, &track.circles[i].center_y);
    FromWgsToPixel(&track.circles[i].side_x, &track.circles[i].side_y);
    FromWgsToPixel(&track.circles[i].angle_x, &track.circles[i].angle_y);
  }
  for (std::size_t i=0; i!=track.eclipses.size(); ++i) {
    FromWgsToPixel(&track.eclipses[i].start_x, &track.eclipses[i].start_y);
    FromWgsToPixel(&track.eclipses[i].center_x, &track.eclipses[i].center_y);
    FromWgsToPixel(&track.eclipses[i].side_x, &track.eclipses[i].side_y);
    FromWgsToPixel(&track.eclipses[i].end_x, &track.eclipses[i].end_y);
    FromWgsToPixel(&track.eclipses[i].angle_x, &track.eclipses[i].angle_y);
  }
  tracks_.push_back(track);
}

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

void OperaOption::pop_track(long long id) {
  std::vector<Track>::iterator iter = tracks_.begin();
  for (; iter != tracks_.end(); ++iter) {
    if (iter->id == id) {
      tracks_.erase(iter);
      return;
    }
  }
}

} //namespace tools
