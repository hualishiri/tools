#ifndef TOOLS_OPERA_RADAR_MECHANICAL_H_
#define TOOLS_OPERA_RADAR_MECHANICAL_H_

#include "opera/radar.h"
#include "opera/track_set.h"

namespace tools {

class RadarNoise;

class MechanicalRadar2D : public Radar2D {
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

  MechanicalRadar2D(Radar* radar, RadarNoise* radar_noise) 
      : radar_(radar), radar_noise_(radar_noise) {}

  virtual void GetState(const TrackSet2D::TrackSetState& track_set_state,
                        RadarState& radar_state);
  virtual long long id() const { return radar_->id; }
  virtual void SetPosition(double x, double y);

  
 private:
  bool IsCaptured(const Point2D& radar, const Point2D& target) const;

  Radar* radar_;
  RadarNoise* radar_noise_;
};

} //namespace tools

#endif //TOOLS_OPERA_RADAR_MECHANICAL_H_
