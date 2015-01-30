#ifndef OPERA_H_
#define OPERA_H_

#include <vector>

#include "track_set.h"
#include "sensor_set.h"

namespace tools {

class Opera2D {
 public:
  struct OperaState {
    TrackSet2D::TrackSetState track_set_state;
    RadarSet2D::RadarSetState radar_set_state;
  };

  class Iterator {
   public:
    Iterator(Opera2D* opera);
    ~Iterator();
    bool Valid() const;
    void Next();
    void Value(OperaState& opera_state);
    void Reset();

  private:
    Opera2D* opera_;
    TrackSet2D::Iterator *iter_track_set_;
  }; 

  Opera2D(TrackSet2D* track_set, RadarSet2D* radar_set)
      : track_set_(track_set), radar_set_(radar_set) {}
  long long GetSumTick() const;

private:
  TrackSet2D* track_set_;
  RadarSet2D* radar_set_;

  friend class Iterator;
};

} //namespace tools

#endif //OPERA_H_
