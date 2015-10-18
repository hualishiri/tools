#ifndef TOOLS_OPERA_TRACK_SET_H_
#define TOOLS_OPERA_TRACK_SET_H_

#include <vector>

#include  "opera/shape.h"
#include "opera/track.h"

namespace tools {

class TrackSet2D {
 public:
  typedef std::vector<Track2D*> TrackSet;
  typedef std::vector<Point2D*> TrackSetPosition;
  typedef std::vector<long long> TrackSetDelay;

  struct TrackSetOption {
    TrackSet* track_set;
    TrackSetPosition* track_set_position;
    TrackSetDelay* track_set_delay;
    double interval;
  };

  struct TrackSetState {
    std::vector<Track2D::TrackState> track_set_state;
    
    bool operator==(const TrackSetState& track_set_state) const;
    friend std::ostream& operator<<(std::ostream& out,
        const TrackSetState& track_set_state);
    friend std::istream& operator>>(std::istream& in,
        TrackSetState& track_set_state);

    friend void ReadFromFile(std::istream& in,
        TrackSet2D::TrackSetState& track_set_state);
    friend void WriteToFile(std::ostream& os,
        const TrackSet2D::TrackSetState& track_set_state);
  };

  class Iterator {
   public:
    Iterator(TrackSet2D* track_set);
    Iterator(const Iterator& iterator);
    Iterator& operator=(const Iterator& iterator);
    ~Iterator();
    bool Valid() const;
    void Next();
    void Value(TrackSetState& track_set_state);
    void Reset();

   private:
    typedef std::vector<Track2D::Iterator> TrackSetIterator;
    std::size_t count_invalid_track_;
    TrackSet2D* track_set_;
    TrackSet* rep_track_set_;
    TrackSetIterator* track_set_iter_;
    TrackSetDelay* track_set_delay_;
    long long tick_current_;

    void PositionChange(const TrackSetPosition& pos,
                        TrackSetState&
                        track_set_state);
  };

  TrackSet2D(const TrackSetOption& track_set_option)
      : rep_track_set_(track_set_option.track_set), 
        track_set_init_pos_(track_set_option.track_set_position),
        track_set_delay_(track_set_option.track_set_delay),
        interval_(track_set_option.interval) {
      assert(track_set_option.track_set->size() ==
          track_set_option.track_set_position->size());
  }
  
  long long GetSumTick() const;
  double GetSumLength() const;
  TrackSet* track_set() const { return rep_track_set_; }
  TrackSetPosition* track_set_position() const {
    return track_set_init_pos_;
  }

 private:
  const Point2D& GetInitPosition(long long id) const;

  TrackSet* rep_track_set_;
  TrackSetPosition* track_set_init_pos_;
  TrackSetDelay* track_set_delay_;
  float interval_;

  friend class Iterator;
};

std::ostream& operator<<(std::ostream& out,
    const TrackSet2D::TrackSetState& track_set_state);
std::istream& operator>>(std::istream& in,
    TrackSet2D::TrackSetState& track_set_state);

void ReadFromFile(std::istream& in, TrackSet2D::TrackSetState& track_set_state);
void WriteToFile(std::ostream& os, const TrackSet2D::TrackSetState& track_set_state);

} //namespace tools

#endif //TOOLS_OPERA_TRACK_SET_H_
