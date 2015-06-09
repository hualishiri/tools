#ifndef TOOLS_OPERA_RADAR_H_
#define TOOLS_OPERA_RADAR_H_

#include "opera/sensor.h"

namespace tools {

class Radar2D : public Sensor {
 public:
  struct RadarError {
    double error_random_distance;
    double error_random_azimuth;
    double error_random_elevation;
    double error_system_distance;
    double error_system_azimuth;
    double error_system_elevation;
    double error_overall_distance;
    double error_overall_azimuth;
    double error_overall_elevation;
  };

  struct RadarState {
    long long id;
    int type;
    Point2D point;
    std::vector<long long> ids;

    std::vector<Point2D> targets;
    std::vector<double> targets_angle_azimuth;
    std::vector<double> targets_real_distance;
    std::vector<double> targets_real_elevation;
    std::vector<double> targets_real_velocity;

    std::vector<Point2D> targets_radar;
    std::vector<double> targets_detected_azimuth;
    std::vector<double> targets_detected_distance;
    std::vector<double> targets_detected_elevation;
    std::vector<double> targets_detected_velocity;

    std::vector<Point2D> targets_filter;

    std::vector<RadarError> targets_error;
  };

  virtual void GetState(const TrackSet2D::TrackSetState& track_set_state,
                        RadarState& radar_state) = 0;
  virtual void SetPosition(double x, double y) = 0;
  virtual long long id() const = 0;
  virtual int type() const = 0;
  virtual long long track_id() const = 0;
};

} //namespace tools

#endif //TOOLS_OPERA_RADAR_H_
