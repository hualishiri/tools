#ifndef SENSOR_H_
#define SENSOR_H_

#include <vector>
#include <string>

#include <stdint.h>

#include "target.h"

namespace tools{

struct SensorState{
  std::vector<TargetState*> target_states;
};

struct SensorOption{
  std::vector<TargetState*> target_states;
};

class Sensor{
public:
  virtual void Initialize(const SensorOption* option) = 0;
  virtual void GetState(SensorState* state) = 0;
};

class Radar : public Sensor{
public:
  virtual void Initialize(const SensorOption* option) = 0;
  virtual void GetState(SensorState* state) = 0;
  
  void set_id(uint64_t id){ id_ = id; }
  void set_name(std::string name){ name_ = name; }
  void set_period(uint16_t period){ period_ = period; }
  void set_min_angle_pitch(uint16_t min_angle_pitch){ 
    min_angle_pitch_ = min_angle_pitch; }
  void set_max_angle_pitch(uint16_t max_angle_pitch){ 
    max_angle_pitch_ = max_angle_pitch; }
  void set_range_azimuth(uint16_t range_azimuth){ 
    range_azimuth_ = range_azimuth; }
  void set_max_distance(uint16_t max_distance){ max_distance_ = max_distance; }
  void set_range_sector(uint16_t range_sector){ range_sector = range_sector_; }

  uint64_t get_id() const { return id_; }
  std::string get_name() const { return name_; }
  uint16_t get_period() const { return period_; }
  uint16_t get_min_angle_pitch() const { return min_angle_pitch_; }
  uint16_t get_max_angle_pitch() const { return max_angle_pitch_; }
  uint16_t get_range_azimuth() const { return range_azimuth_; }
  uint16_t get_max_distance() const { return max_distance_;  }
  uint16_t get_range_sector() const { return range_sector_;  }


private:
  SensorOption* option_;
  uint64_t id_;                        //!< 序列号
  std::string name_;                   //!< 雷达名字
  uint16_t period_;                    //!< 扫描周期（ms）
  uint16_t min_angle_pitch_;           //!< 最小俯仰角（度）
  uint16_t max_angle_pitch_;           //!< 最大俯仰角（度）
  uint16_t range_azimuth_;             //!< 方位角范围大小（度）
  uint16_t max_distance_;              //!< 最大探测距离（千米）
  uint16_t range_sector_;              //!< 扇扫角度（度）
};

}

#endif //SENSOR_H_
