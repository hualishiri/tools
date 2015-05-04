#include "opera/opera_option.h"

#include <assert.h>

#include "map/map_projection.h"
#include "util/tool.h"
//#include "util/logger.h"

namespace tools {

OperaOption* OperaOption::opera_option_ = 0;

OperaOption* OperaOption::Instance() {
  if (opera_option_ == 0)
    opera_option_ = new OperaOption();
  return opera_option_;
}


void OperaOption::push_back_radar(Radar& radar) {
  assert(radar.id > 0);
  assert(ValidOfLongitude(radar.start_x));
  assert(ValidOfLatitude(radar.start_y));
  assert(ValidOfLongitude(radar.radius_x));
  assert(ValidOfLatitude(radar.radius_y));
  assert(radar.level_noise >= 0.0 && radar.level_noise <= 256.0);
  assert(ValidOfCircleAngle(radar.angle_azimuth));
  assert(ValidOfCircleAngle(radar.angle_sector_range));
  assert(radar.error_system >= -10.0 && radar.error_system <= 10.0);
  assert(radar.error_random >= -10.0 && radar.error_random <= 10.0);
  assert(radar.error_overall >= -10.0 && radar.error_overall <= 10.0);
  radar.level_noise = 0.3 * radar.error_system + 0.3 * radar.error_random
    + 0.4 * radar.error_overall;
  radars_.push_back(radar);
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

void OperaOption::push_back_track(Track& track) {
  assert(track.lines.size() + track.circles.size()
      + track.eclipses.size() == track.types.size());
  assert(track.ids.size() == static_cast<std::size_t>(track.batch_count));
  assert(track.level_noise_track >= 0.0 && track.level_noise_track <= 256);
  assert(track.id >= 0);
  for (std::size_t i = 0; i != track.start_speeds.size(); ++i)
    assert(track.start_speeds[i] >= 0.0 && track.start_speeds[i] <= 10);
  tracks_.push_back(track); 
}

void OperaOption::ConvertToPixel() {
  for (std::size_t i=0; i!=radars_.size(); ++i) {
    FromWgsToPixel(&radars_[i].start_x, &radars_[i].start_y);
    FromWgsToPixel(&radars_[i].radius_x, &radars_[i].radius_y);
  }  
  for (std::size_t i=0; i!=tracks_.size(); ++i) {
    for (std::size_t j=0; j!=tracks_[i].lines.size(); ++j) {
      FromWgsToPixel(&tracks_[i].lines[j].start_x,
                     &tracks_[i].lines[j].start_y);
      FromWgsToPixel(&tracks_[i].lines[j].end_x,
                     &tracks_[i].lines[j].end_y);
    }
    for (std::size_t j=0; j!=tracks_[i].circles.size(); ++j) {
      FromWgsToPixel(&tracks_[i].circles[j].start_x,
                     &tracks_[i].circles[j].start_y);
      FromWgsToPixel(&tracks_[i].circles[j].center_x,
                     &tracks_[i].circles[j].center_y);
      FromWgsToPixel(&tracks_[i].circles[j].side_x,
                     &tracks_[i].circles[j].side_y);
      FromWgsToPixel(&tracks_[i].circles[j].angle_x,
                     &tracks_[i].circles[j].angle_y);
    }
    for (std::size_t j=0; j!=tracks_[i].eclipses.size(); ++j) {
      FromWgsToPixel(&tracks_[i].eclipses[j].start_x,
                     &tracks_[i].eclipses[j].start_y);
      FromWgsToPixel(&tracks_[i].eclipses[j].center_x,
                     &tracks_[i].eclipses[j].center_y);
      FromWgsToPixel(&tracks_[i].eclipses[j].side_x,
                     &tracks_[i].eclipses[j].side_y);
      FromWgsToPixel(&tracks_[i].eclipses[j].end_x,
                     &tracks_[i].eclipses[j].end_y);
      FromWgsToPixel(&tracks_[i].eclipses[j].angle_x,
                     &tracks_[i].eclipses[j].angle_y);
    }
  }
}

std::vector<OperaOption::TrackInternal> OperaOption::tracks() const { 
  std::vector<TrackInternal> track_internals;
  std::size_t track_batch_count = 0;
  for (std::size_t i=0; i!=tracks_.size(); ++i) {
    track_batch_count = static_cast<std::size_t>(tracks_[i].batch_count);
    for (std::size_t j=0; j!=track_batch_count; ++j) {
      TrackInternal track_internal = {
        tracks_[i].ids[j],
        tracks_[i].start_speeds[j],
        tracks_[i].accelerations[j],
        tracks_[i].time_delays[j],
        tracks_[i].lines,
        tracks_[i].circles,
        tracks_[i].eclipses,
        tracks_[i].types
      };
      if (0 != j)
        TrackInternalSift(track_internal, tracks_[i].level_noise_track, j);
      track_internals.push_back(track_internal);
    }
  }
  return track_internals;
}

void OperaOption::TrackInternalSift(TrackInternal& track_internal,
                                    double level_noise,
                                    int seed) const{
  double x_sift = GetRandNumber(seed + 1) * level_noise;
  double y_sift = GetRandNumber(seed + 2) * level_noise;
  for (std::size_t i=0; i!=track_internal.lines.size(); ++i) {
    track_internal.lines[i].start_x += x_sift;
    track_internal.lines[i].start_y += y_sift;
    track_internal.lines[i].end_x += x_sift;
    track_internal.lines[i].end_y += y_sift;
  }
  for (std::size_t i=0; i!=track_internal.circles.size(); ++i) {
    track_internal.circles[i].start_x += x_sift;
    track_internal.circles[i].start_y += y_sift;
    track_internal.circles[i].center_x+= x_sift;
    track_internal.circles[i].center_y += y_sift;
    track_internal.circles[i].side_x += x_sift;
    track_internal.circles[i].side_y += y_sift;
    track_internal.circles[i].angle_x += x_sift;
    track_internal.circles[i].angle_y += y_sift;
  }
}

} //namespace tools
