#ifndef TOOLS_OPERA_RADAR_SECTOR_H_
#define TOOLS_OPERA_RADAR_SECTOR_H_

#include <assert.h>

#include <vector>

#include "opera/radar.h"
#include "opera/radar_noise.h"
#include "opera/track_set.h"
#include "util/tool.h"

namespace tools {

class SectorRadar : public Radar2D {
 public:
  struct Radar {
    long long id;
    int type;
    double x;
    double y;
    long long track_id;
    std::vector<std::pair<double, double> > azimuth_range;
    double distance_detect;
    double level_noise;
    int detecting_objects_types;
  };

  struct Target {
    double x;
    double y;
    int target_type;
  };

  SectorRadar(Radar* radar, RadarNoise* radar_noise)
    : radar_(radar), radar_noise_(radar_noise) {
    assert(radar_->id > 0);

    for (std::size_t i=0; i!=radar->azimuth_range.size(); ++i) {
      assert(radar_->azimuth_range[i].first >= 0.0 && 
          radar_->azimuth_range[i].first <= 2.0 * T_PI);
      assert(radar_->azimuth_range[i].second >= 0.0 &&
          radar_->azimuth_range[i].second <= 2.0 * T_PI);
    }

    assert(radar_->distance_detect >= 0.0);
  }

  virtual void GetState(const TrackSet2D::TrackSetState& track_set_state,
                        RadarState& radar_state);
  virtual void SetPosition(double x, double y);
  virtual long long id() const { return radar_->id; }
  virtual int type() const { return radar_->type; }
  virtual long long track_id() const { return radar_->track_id; }

 private:
  bool IsCaptured(const Radar& radar, const Target& target) const;
  float GetAngleOfAzimuth(const Point2D& radar, const Point2D& target) const;
  bool IsInRange(const std::vector<std::pair<double, double> > azimuth_range,
                 double angle_azimuth_radar) const;

  Radar* radar_;
  RadarNoise* radar_noise_;
};

} //namespace tools

#endif //TOOLS_OPERA_RADAR_SECTOR_H_
