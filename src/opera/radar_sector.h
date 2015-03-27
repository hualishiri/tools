#ifndef TOOLS_OPERA_RADAR_SECTOR_H_
#define TOOLS_OPERA_RADAR_SECTOR_H_

#include <assert.h>

#include "opera/radar.h"
#include "opera/radar_noise.h"
#include "opera/track_set.h"
#include "util/tool.h"

namespace tools {

class SectorRadar : public Radar2D {
 public:
  struct Radar {
    long long id;
    double x;
    double y;
    double angle_azimuth;
    double angle_sector_range;
    double distance_detect;
    double level_noise;
  };

  SectorRadar(Radar* radar, RadarNoise* radar_noise)
    : radar_(radar), radar_noise_(radar_noise) {
    assert(radar_->id > 0);
    assert(radar_->angle_azimuth >= 0.0 && radar_->angle_azimuth <= 2 * T_PI);
    assert(radar_->angle_sector_range >= 0.0 &&
        radar_->angle_sector_range <= 2 * T_PI);
    assert(radar_->distance_detect >= 0.0);
  }

  virtual void GetState(const TrackSet2D::TrackSetState& track_set_state,
                        RadarState& radar_state);

 private:
  bool IsCaptured(const Point2D& radar, const Point2D& target) const;

  Radar* radar_;
  RadarNoise* radar_noise_;
};

} //namespace tools

#endif //TOOLS_OPERA_RADAR_SECTOR_H_
