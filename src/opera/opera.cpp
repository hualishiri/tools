#include "opera/opera.h"

#include <vector>

#include "opera/acceleration.h"
#include "opera/circle.h"
#include "opera/line.h"
#include "opera/opera_option.h"
#include "opera/radar_mechanical.h"
#include "util/tool.h"

namespace tools {

void Opera2D::Initialize(const OperaOption& opera_option) {
  BuildRadar(opera_option);
  BuildTrack(opera_option);
}

void Opera2D::BuildRadar(const OperaOption& opera_option) {
  RadarSet2D::RadarSet* rep_radar_set = new RadarSet2D::RadarSet();
  std::vector<OperaOption::Radar> radars = opera_option.radars();
  double radius = 0.0;
  for (std::size_t i = 0; i != radars.size(); ++i) {
    radius = sqrt(pow(radars[i].start_x - radars[i].radius_x, 2)
        + pow(radars[i].start_y - radars[i].radius_y, 2));
    rep_radar_set->push_back(new MechanicalRadar2D(radars[i].id,
        radars[i].radius_x,
        radars[i].radius_y,
        radius));
  }
  radar_set_ = new RadarSet2D(rep_radar_set);
}

void Opera2D::BuildTrack(const OperaOption& opera_option) {
  TrackSet2D::TrackSet *track_set_rep = new TrackSet2D::TrackSet();
  std::vector<OperaOption::Track> tracks
       = opera_option.tracks();
  std::vector<OperaOption::TrackUnitType> tracks_type;
  TrackSet2D::TrackSetPosition* track_set_position
       = new TrackSet2D::TrackSetPosition();;
  for(int i=0; i != tracks.size(); ++i) {
    Track2D::TrackUnitSet* track_unit_set = new Track2D::TrackUnitSet();
    int index_line = 0;
    int index_circle = 0;
    int index_eclipse = 0;
    for (int j = 0; j != tracks[i].types.size(); ++j) {
      Shape2D* shape = 0;
      if (tracks[i].types[j] == OperaOption::LINE) {
        if (j == 0)
          track_set_position->push_back(new Point2D(
              tracks[i].lines[index_line].start_x,
              tracks[i].lines[index_line].start_y));
        shape = new Line2D(Point2D(
            tracks[i].lines[index_line].end_x
            - tracks[i].lines[index_line].start_x,
            tracks[i].lines[index_line].end_y 
            - tracks[i].lines[index_line].start_y));
        ++index_line;
      } else if (tracks[i].types[j] == OperaOption::CIRCLE) {
        if (j == 0)
          track_set_position->push_back(new Point2D(
              tracks[i].circles[index_circle].start_x,
              tracks[i].circles[index_circle].start_y));
          shape = new Circle2D(Point2D(
              tracks[i].circles[index_circle].center_x
              - tracks[i].circles[index_circle].start_x,
              tracks[i].circles[index_circle].center_y
              - tracks[i].circles[index_circle].start_y),
          AngleFromStartByClockInCircle(tracks[i].circles[index_circle].start_x,
              tracks[i].circles[index_circle].start_y,
              tracks[i].circles[index_circle].center_x,
              tracks[i].circles[index_circle].center_y,
              tracks[i].circles[index_circle].angle_x,
              tracks[i].circles[index_circle].angle_y));
          ++index_circle;
     }
    Track2D* track = new Track2D(tracks[i].id,
        track_unit_set,
        opera_option.interval(),
        tracks[i].start_speed);
    track_set_rep->push_back(track);
  }
  track_set_ = new TrackSet2D(track_set_rep,
      track_set_position,
      opera_option.interval());
}

long long Opera2D::GetSumTick() const {
  return track_set_->GetSumTick();
}

Opera2D::Iterator::Iterator(Opera2D* opera) {
  opera_ = opera;
  iter_track_set_ = new TrackSet2D::Iterator(opera_->track_set_);
}

Opera2D::Iterator::~Iterator() {
  delete iter_track_set_;
}

bool Opera2D::Iterator::Valid() const {
  return iter_track_set_->Valid();
}

void Opera2D::Iterator::Next() {
  iter_track_set_->Next();
}

void Opera2D::Iterator::Value(OperaState& opera_state) {
  iter_track_set_->Value(opera_state.track_set_state);
  opera_->radar_set_->GetState(opera_state.track_set_state, 
                               opera_state.radar_set_state);
}

void Opera2D::Iterator::Reset() {
  iter_track_set_->Reset();
}

} //namespace tools
