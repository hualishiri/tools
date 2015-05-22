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
    //double angle_azimuth;
    //double angle_sector_range;
    std::vector<std::pair<double, double> > azimuth_range;
    double distance_detect;
    double level_noise;
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
 private:
  bool IsCaptured(const Point2D& radar, const Point2D& target) const;
  float GetAngleOfAzimuth(const Point2D& radar, const Point2D& target) const;
  inline long long id() const { return radar_->id; }
  bool IsInRange(const std::vector<std::pair<double, double> > azimuth_range,
                 double angle_azimuth_radar) const;

  Radar* radar_;
  RadarNoise* radar_noise_;
};

} //namespace tools

#endif //TOOLS_OPERA_RADAR_SECTOR_H_
