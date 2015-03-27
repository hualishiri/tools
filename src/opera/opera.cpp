#include "opera/opera.h"

#include <vector>

#include "opera/acceleration.h"
#include "opera/circle.h"
#include "opera/line.h"
#include "opera/opera_option.h"
#include "opera/radar_sector.h"
#include "opera/radar_mechanical.h"
#include "opera/radar_noise_gauss.h"
#include "util/logger.h"
#include "util/tool.h"

namespace tools {

void Opera2D::Initialize(const OperaOption& opera_option) {
  BuildRadar(opera_option);
  BuildTrack(opera_option);
}

void Opera2D::BuildRadar(const OperaOption& opera_option) {
  RadarSet2D::RadarSet* rep_radar_set = new RadarSet2D::RadarSet();
  std::vector<OperaOption::Radar> radars = opera_option.radars();
  //double radius = 0.0;
  for (std::size_t i = 0; i != radars.size(); ++i) {
    /*radius = sqrt(pow(radars[i].start_x - radars[i].radius_x, 2)
        + pow(radars[i].start_y - radars[i].radius_y, 2));
    rep_radar_set->push_back(new MechanicalRadar2D(radars[i].id,
        radars[i].radius_x,
        radars[i].radius_y,
        radius));*/

    MechanicalRadar2D::Radar* radar = new MechanicalRadar2D::Radar();
    radar->id = radars[i].id;
    radar->x = radars[i].radius_x;
    radar->y = radars[i].radius_y;
    radar->angle_azimuth = 0.0;
    radar->angle_sector_range = 2 * 3.1415;
    radar->distance_detect = sqrt(pow(radars[i].start_x - radars[i].radius_x, 2)
        + pow(radars[i].start_y - radars[i].radius_y, 2));

    radar->level_noise = radars[i].level_noise;
    RadarNoise* radar_noise = new RadarNoiseGauss(radar->level_noise);

    MechanicalRadar2D* sector_radar = new MechanicalRadar2D(radar, radar_noise);
    rep_radar_set->push_back(sector_radar);
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
  double old_speed = 0.0;
  double current_speed = 0.0;
  for(std::size_t i=0; i != tracks.size(); ++i) {
    Track2D::TrackUnitSet* track_unit_set = new Track2D::TrackUnitSet();
    int index_line = 0;
    int index_circle = 0;
    for (std::size_t j = 0; j != tracks[i].types.size(); ++j) {
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
      } else if (tracks[i].types[j] == OperaOption::ECLIPSE) { }
      Acceleration* acc_uniform = new ConstantAcceleration(
          tracks[i].acceleration);
      if (0 == j)
       current_speed = tracks[i].start_speed;
     else
       current_speed = old_speed; 
     assert(0 != shape);
     TrackUnit* track_unit = new TrackUnit(shape,
                                           acc_uniform,
                                           opera_option.interval(),
                                           current_speed);
      if (0 == track_unit)
        LogInfo("TrackUnit Initial Fail");
      old_speed = track_unit->GetEndSpeed();
      track_unit_set->push_back(track_unit);
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

void Opera2D::Release() {
  if (0 != radar_set_) {
    std::size_t length = radar_set_->radar_set()->size();
    RadarSet2D::RadarSet* radar_set = radar_set_->radar_set();
    for (std::size_t i=0; i!=length; ++i)
      delete (*radar_set)[i];
    delete radar_set;
    delete radar_set_;
    radar_set_ = 0;
  }
  if (0 != track_set_) {
    std::size_t length = track_set_->track_set()->size(); 
    TrackSet2D::TrackSet* track_set = track_set_->track_set();
    for (std::size_t i=0; i!=length; ++i) {
      std::size_t len_track_unit = (*track_set)[i]->track_unit_set()->size();
      Track2D::TrackUnitSet* track_unit_set = (*track_set)[i]->track_unit_set();
      for (std::size_t j=0; j!=len_track_unit; ++j) {
        delete (*track_unit_set)[j]->shape();
        delete (*track_unit_set)[j]->acceleration();
        delete (*track_unit_set)[j];
      } 
      delete track_unit_set;
      delete (*track_set)[i];
    }
    delete track_set;
    delete track_set_;
    TrackSet2D::TrackSetPosition* track_set_pos = track_set_->track_set_position();
    length = track_set_->track_set_position()->size();
    for (std::size_t i=0; i!=length; ++i)
      delete (*track_set_pos)[i];
    track_set_ = 0;
  }
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

void Opera2D::OperaState::ConvertToWgs() {
  for (std::size_t i=0;
      i!=radar_set_state.radar_set_state.size();
      ++i)
    for (std::size_t j=0;
        j!=radar_set_state.radar_set_state[i].targets.size();
        ++j)
      FromPixelToWgs(&radar_set_state.radar_set_state[i].targets[j].x,
                     &radar_set_state.radar_set_state[i].targets[j].y);
  for (std::size_t i=0;
       i!=track_set_state.track_set_state.size();
       ++i)
    FromPixelToWgs(&track_set_state.track_set_state[i].point.x,
                   &track_set_state.track_set_state[i].point.y);
}

void Opera2D::Iterator::Reset() {
  iter_track_set_->Reset();
}

} //namespace tools
