#ifndef TOOLS_OPERA_RADAR_H_
#define TOOLS_OPERA_RADAR_H_

#include "opera/sensor.h"

#include <iostream>

namespace tools {

class Radar2D : public Sensor {
 public:
  struct RadarError {
    //距离的随机误差，单位：和OperaOption::Radar中的相同
    double error_random_distance;

    //方位角的随机误差，单位：弧度
    double error_random_azimuth;

    //俯仰角的随机误差，单位：弧度
    double error_random_elevation;

    //距离的系统误差，单位：由使用者决定
    double error_system_distance;

    //方位角的系统误差，单位：弧度
    double error_system_azimuth;

    //俯仰角的系统误差，单位：弧度
    double error_system_elevation;

    //距离的系统误差，单位：由使用者决定
    double error_overall_distance;

    //方位角的系统误差，单位：弧度
    double error_overall_azimuth;

    //俯仰角的系统误差，单位：弧度
    double error_overall_elevation;

    double error_distance;
    double error_velocity;
    double error_direction;

    bool operator==(const RadarError& radar_error) const;

    friend std::ostream& operator<<(std::ostream& out,
                                    const RadarError& radar_error);
    friend std::istream& operator>>(std::istream& in, RadarError& radar_error);
  };

  struct RadarState {
    long long id;

    //雷达所探测目标的类型
    int type;

    //雷达的位置
    Point2D point;

    double height;

    //该雷达探测到的所有目标id
    std::vector<long long> ids;

    //目标位置，单位：由使用者决定
    std::vector<Point2D> targets;

    //目标高度，单位：由使用者决定
    std::vector<double> targets_height;

    //目标的方位角，单位：弧度
    std::vector<double> targets_angle_azimuth;

    //目标距离雷达的距离，单位：单位：由使用者决定
    std::vector<double> targets_real_distance;

    //目标的真实的俯仰角，单位：弧度
    std::vector<double> targets_real_elevation;

    //目标的真实的速度，单位：单位：由使用者决定
    std::vector<double> targets_real_velocity;

    //目标的真实的航向，单位：单位：弧度
    std::vector<double> targets_real_course;

    //雷达探测到的目标所在位置，单位：由使用者决定
    std::vector<Point2D> targets_radar;

    //雷达探测到的目标所在高度，单位：由使用者决定
    std::vector<double> targets_radar_height;

    //雷达探测到的目标的方位角，单位：弧度
    std::vector<double> targets_detected_azimuth;

    //雷达探测到的目标距离雷达的距离，单位：由使用者决定
    std::vector<double> targets_detected_distance;

    //雷达探测到的目标俯仰角，单位：弧度
    std::vector<double> targets_detected_elevation;

    //雷达探测到的目标的速度，单位：单位：由使用者决定
    std::vector<double> targets_detected_velocity;

    //雷达探测到的目标的航向，单位：弧度
    std::vector<double> targets_detected_course;

    //暂时无用
    std::vector<Point2D> targets_filter;

    //本次雷达探测到的目标所有误差
    std::vector<RadarError> targets_error;

    bool operator==(const RadarState& lhs) const;

    friend std::ostream& operator<<(std::ostream& out,
                                    const RadarState& radar_state);
    friend std::istream& operator>>(std::istream& in, RadarState& radar_state);

    unsigned char get_type_trival() const {
      int val = type;
      val = (val >> 8) & 0x0ff;
      return val;
    };
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
