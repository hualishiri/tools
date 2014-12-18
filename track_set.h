#ifndef TOOLS_TRACK_SET_H_
#define TOOLS_TRACK_SET_H_

namespace tools{

class TrackSet2D{
public:
  typedef std::vector<Track2D*> TrackSet;
  typedef std::vector<Point2D*> TrackSetPosition;
  struct TrackSetState{
    std::vector<Track2D::TrackState> track_set_state;
  };
  class Iterator{
  public:
    void Valid() const;
    void Next();
    void Value(TrackSetState& track_set_state);
    void Reset();
  };

  TrackSet2D(TrackSet* track_set,
      TrackSetPosition* track_set_init_pos):track_set_(track_set){}
private:
  TrackSet *track_set_;
  TrackSetPosition* track_set_init_pos_;
};

} //namespace tools

#endif //TOOLS_TRACK_SET_H_
