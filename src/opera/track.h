#ifndef TOOLS_OPERA_TRACK_H_
#define TOOLS_OPERA_TRACK_H_

#include <vector>

#include "opera/shape.h"
#include "opera/track_unit.h"

namespace tools {

class Track2D{
public:
  typedef std::vector<TrackUnit*> TrackUnitSet;
  struct TrackState{
    long long id;

    //目标当前的位置
    Point2D point;

    //当前的机器时钟
    long long tick;

    //目标的加速度，单位：由使用者决定
    float acc;
    
    //目标的速度，单位：由使用者决定
    float speed;

    //目标距离初始位置的距离，单位：由使用者决定
    double distance;

    //目标的方位角,单位：由使用者决定
    float azimuth;

    //目标的类型
    int track_type;
  };

  class Iterator{
  public:
    explicit Iterator(Track2D* track);
    Iterator(const Iterator& iterator);
    Iterator& operator=(const Iterator& iterator);
    ~Iterator();
    bool Valid() const;
    void Next();
    void Reset();
    void Value(TrackState& track_state);

  private:
    float Azimuth(float x, float y) const;

    float interval_;
    //float speed_current_;
    long long tick_current_;
    long long kTickSum_;
    double distance_current_;
    double distance_dot_;
    Point2D origin_current_;
    Point2D temp_;
    TrackUnit::TrackUnitState track_unit_state_;
    Track2D* track_;
    Track2D::TrackUnitSet::iterator iter_track_;
    TrackUnit::Iterator *iter_track_unit_;
    double last_x_;
    double last_y_;
  };
  //return the length of the track
  double GetLength() const;
  long long GetSumTick() const;

  Track2D(long long id, 
      TrackUnitSet* track_unit_set, 
      long long interval, 
      float init_speed)
    :id_(id),
    track_unit_set_(track_unit_set), 
    init_speed_(init_speed), 
    interval_(interval){
      track_type_ = ~0x00;
    }
  long long id(){ return id_; }
  TrackUnitSet* track_unit_set() const { return track_unit_set_; }
  int track_type() const { return track_type_; }
  void set_track_type(int track_type) { track_type_ = track_type; }
    
private:
  long long id_;
  TrackUnitSet* track_unit_set_;
  float init_speed_;
  const long long interval_;    //the inverval of iteration
  int track_type_;

  Track2D(const Track2D&);
  Track2D& operator=(const Track2D&);

  friend class Iterator;
};

} //namespace tools

#endif //TOOLS_OPERA_TRACK_H_
