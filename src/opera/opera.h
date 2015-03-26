#ifndef TOOLS_OPERA_OPERA_H_
#define TOOLS_OPERA_OPERA_H_

#include "opera/opera_option.h"
#include "opera/radar_set.h"
#include "opera/track_set.h"

namespace tools {

class Opera2D {
 public:
  struct OperaState {
    void ConvertToWgs();

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

  Opera2D() : track_set_(0), radar_set_(0) {}
  Opera2D(TrackSet2D* track_set, RadarSet2D* radar_set)
    : track_set_(track_set), radar_set_(radar_set) {
  }

  long long GetSumTick() const;
  void Initialize(const OperaOption& opera_option);
  void Release();

 private:
  void BuildRadar(const OperaOption& opera_option);
  void BuildTrack(const OperaOption& opera_option);

  TrackSet2D* track_set_;
  RadarSet2D* radar_set_;

  friend class Iterator;
};

} //namespace tools

#endif //TOOLS_OPERA_OPERA_H_
