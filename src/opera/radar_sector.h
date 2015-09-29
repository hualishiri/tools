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
    double height;
    long long track_id;
    std::vector<std::pair<double, double> > azimuth_range;
    double distance_detect;
    double level_noise;
    int detecting_objects_types;
    
    double error_random_distance;
    double error_random_azimuth;
    double error_random_elevation;
    double error_system_distance;
    double error_system_azimuth;
    double error_system_elevation;
  };

  struct Target {
    double x;
    double y;
    int target_type;
  };

  SectorRadar(Radar* radar, RadarNoise* radar_noise);

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
  void CalculateRadarError(int seed);
  void CalculateRadarState(RadarState& radar_state);
  void CalculateObjectPosition(const Point2D& radar,
                               double azimuth,
                               double distance,
                               Point2D& target);
  void CalculateObjectCourse(RadarState& radar_state);
  void ClearRadarState(RadarState& radar_state) const;

  Radar* radar_;
  RadarNoise* radar_noise_;
  RadarError error_;
  RadarState radar_state_last_;
};

} //namespace tools

#endif //TOOLS_OPERA_RADAR_SECTOR_H_
