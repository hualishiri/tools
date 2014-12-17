#ifndef TOOLS_DLDB_TRACK_H_

#define TOOLS_DLDB_TRACK_H_

#include <stdint.h>

#include<vector>
#include<cstddef>
#include<string>

#include "shape.h"
#include "track_unit.h"

namespace tools{

class TrackUnit;
class Point2D;

class Track2D{
public:
  typedef std::vector<TrackUnit*> TrackUnitSet;
  struct TrackState{
    Point2D point;
    unsigned long long tick;
    float acc;
    float speed;
    double distance;
  };
  class Iterator{
  public:
    explicit Iterator(Track2D* track);
    bool Valid() const;
    void Next();
    void Reset();
    void Value(TrackState& track_state) const;
  private:
    float interval_;
    float speed_current_;
    unsigned long long tick_current_;
    long long kTickSum_;
    long long distance_current_;
    double distance_dot_;
    Point2D origin_current_;
    Point2D temp_;
    TrackUnit::TrackUnitState track_unit_state_;
    Track2D* track_;
    Track2D::TrackUnitSet::iterator iter_track_;
    TrackUnit::Iterator *iter_track_unit_;
  };
  //return the length of the track
  double GetLength() const;
  long long GetSumTick() const;

  Track2D(TrackUnitSet* track_unit_set, float init_speed, long long interval)
    :track_unit_set_(track_unit_set), init_speed_(init_speed), interval_(interval){}
    
private:
  TrackUnitSet* track_unit_set_;
  float init_speed_;
  const long long interval_;    //the inverval of iteration

  Track2D(const Track2D&);
  Track2D& operator=(const Track2D&);

  friend class Iterator;
};

} //namespace tools

#endif //TOOLS_DLDB_TRACK_H_
