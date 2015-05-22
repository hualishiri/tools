#include "opera/opera.h"

#include <assert.h>

#include <vector>

#include "opera/acceleration.h"
#include "opera/circle.h"
#include "opera/line.h"
#include "opera/opera_option.h"
#include "opera/radar_sector.h"
#include "opera/radar_mechanical.h"
#include "opera/radar_noise_gauss.h"
#include "util/tool.h"

namespace tools {

void Opera2D::Initialize(const OperaOption& opera_option) {
  BuildRadar(opera_option);
  BuildTrack(opera_option);
}

void Opera2D::BuildRadar(const OperaOption& opera_option) {
  RadarSet2D::RadarSet* rep_radar_set = new RadarSet2D::RadarSet();
  std::vector<OperaOption::Radar> radars = opera_option.radars();
  for (std::size_t i = 0; i != radars.size(); ++i) {
    SectorRadar::Radar* radar = new SectorRadar::Radar();
    radar->id = radars[i].id;
    radar->type = radars[i].type;
    radar->x = radars[i].radius_x;
    radar->y = radars[i].radius_y;
    radar->angle_azimuth = radars[i].angle_azimuth;
    radar->angle_sector_range = radars[i].angle_sector_range;
    radar->distance_detect = Distance2DArc(radars[i].start_x,
                                           radars[i].start_y,
                                           radars[i].radius_x,
                                           radars[i].radius_y);

    radar->level_noise = radars[i].level_noise;
    RadarNoise* radar_noise = new RadarNoiseGauss(radar->level_noise);
    SectorRadar* sector_radar = new SectorRadar(radar, radar_noise);
    rep_radar_set->push_back(sector_radar);
  }
  radar_set_ = new RadarSet2D(rep_radar_set);
}

void Opera2D::BuildTrack(const OperaOption& opera_option) {
  TrackSet2D::TrackSet *track_set_rep = new TrackSet2D::TrackSet();
  std::vector<OperaOption::TrackInternal> tracks
       = opera_option.tracks();
  std::vector<OperaOption::TrackUnitType> tracks_type;
  TrackSet2D::TrackSetPosition* track_set_position
       = new TrackSet2D::TrackSetPosition();;
  double old_speed = 0.0;
  double current_speed = 0.0;
  TrackSet2D::TrackSetDelay* track_set_delay = new TrackSet2D::TrackSetDelay();
  for(std::size_t i=0; i != tracks.size(); ++i) {
    track_set_delay->push_back(tracks[i].time_delay / opera_option.interval());
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
          tracks[i].acceleration[j]);

      if (0 == j)
       current_speed = tracks[i].start_speed;
     else
       current_speed = old_speed; 
     assert(0 != shape);
     TrackUnit* track_unit = new TrackUnit(shape,
                                           acc_uniform,
                                           opera_option.interval(),
                                           current_speed);
      old_speed = track_unit->GetEndSpeed();
      track_unit_set->push_back(track_unit);
    }
    Track2D* track = new Track2D(tracks[i].id,
        track_unit_set,
        opera_option.interval(),
        tracks[i].start_speed);
    track_set_rep->push_back(track);
  }
  TrackSet2D::TrackSetOption track_set_option = {
    track_set_rep,
    track_set_position,
    track_set_delay,
    opera_option.interval()
  };
  track_set_ = new TrackSet2D(track_set_option);
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
  ChangeRadarPosition(opera_state);
  opera_->radar_set_->GetState(opera_state.track_set_state, 
                               opera_state.radar_set_state);
  OperaAnalysis::Handle(opera_state.radar_set_state,
                       opera_state.opera_analysis_state);
}

void Opera2D::OperaState::ConvertToWgs() {
  for (std::size_t i=0;
      i!=radar_set_state.radar_set_state.size();
      ++i) {
    FromPixelToWgs(&radar_set_state.radar_set_state[i].point.x,
                   &radar_set_state.radar_set_state[i].point.y);
    for (std::size_t j=0;
        j!=radar_set_state.radar_set_state[i].targets.size();
        ++j) {
      FromPixelToWgs(&radar_set_state.radar_set_state[i].targets[j].x,
                     &radar_set_state.radar_set_state[i].targets[j].y);
      FromPixelToWgs(&radar_set_state.radar_set_state[i].targets_radar[j].x,
                     &radar_set_state.radar_set_state[i].targets_radar[j].y);
      FromPixelToWgs(&radar_set_state.radar_set_state[i].targets_filter[j].x,
                     &radar_set_state.radar_set_state[i].targets_filter[j].y);
    }
  }
  for (std::size_t i=0;
       i!=track_set_state.track_set_state.size();
       ++i)
    FromPixelToWgs(&track_set_state.track_set_state[i].point.x,
                   &track_set_state.track_set_state[i].point.y);
}

void Opera2D::OperaState::ConvertToWgs(void (Conv)(double*, double*)) {
  for (std::size_t i=0;
      i!=radar_set_state.radar_set_state.size();
      ++i) {
    Conv(&radar_set_state.radar_set_state[i].point.x,
                   &radar_set_state.radar_set_state[i].point.y);
    for (std::size_t j=0;
        j!=radar_set_state.radar_set_state[i].targets.size();
        ++j) {
      Conv(&radar_set_state.radar_set_state[i].targets[j].x,
                     &radar_set_state.radar_set_state[i].targets[j].y);
      Conv(&radar_set_state.radar_set_state[i].targets_radar[j].x,
                     &radar_set_state.radar_set_state[i].targets_radar[j].y);
      Conv(&radar_set_state.radar_set_state[i].targets_filter[j].x,
                     &radar_set_state.radar_set_state[i].targets_filter[j].y);
    }
  }
  for (std::size_t i=0;
       i!=track_set_state.track_set_state.size();
       ++i)
    Conv(&track_set_state.track_set_state[i].point.x,
                   &track_set_state.track_set_state[i].point.y);
}

void Opera2D::Iterator::Reset() {
  iter_track_set_->Reset();
}

void Opera2D::Iterator::ChangeRadarPosition(OperaState& opera_state) {
  std::size_t size_radar = opera_->radar_set_->radar_set()->size();
  std::size_t size_track = opera_state.track_set_state.track_set_state.size();
  for (std::size_t i=0; i!=size_radar; ++i) {
    for (std::size_t j=0; j!=size_track; ++j) {
      if ((*(opera_->radar_set_->radar_set()))[i]->id() 
          == opera_state.track_set_state.track_set_state[j].id) {
        (*(opera_->radar_set_->radar_set()))[i]->SetPosition(
            opera_state.track_set_state.track_set_state[j].point.x,
            opera_state.track_set_state.track_set_state[j].point.y);
      }
    }
  }
}

std::ostream& operator<<(std::ostream& out,
                         const Opera2D::OperaState& opera_state) {
  out << opera_state.track_set_state.track_set_state.size() << " ";
  std::size_t size_track = opera_state.track_set_state.track_set_state.size();
  for (std::size_t i=0; i!=size_track; ++i) {
    out << opera_state.track_set_state.track_set_state[i].id << " "
        << opera_state.track_set_state.track_set_state[i].point.x << " "
        << opera_state.track_set_state.track_set_state[i].point.y << " "
        << opera_state.track_set_state.track_set_state[i].tick << " "
        << opera_state.track_set_state.track_set_state[i].acc << " "
        << opera_state.track_set_state.track_set_state[i].speed << " "
        << opera_state.track_set_state.track_set_state[i].distance << " "
        << opera_state.track_set_state.track_set_state[i].azimuth << " ";
  }

  out << opera_state.radar_set_state.radar_set_state.size() << " ";
  std::size_t size_radar = opera_state.radar_set_state.radar_set_state.size();
  for (std::size_t i=0; i!=size_radar; ++i) {
    out << opera_state.radar_set_state.radar_set_state[i].id << " "
        << opera_state.radar_set_state.radar_set_state[i].type<< " "
        << opera_state.radar_set_state.radar_set_state[i].point.x << " "
        << opera_state.radar_set_state.radar_set_state[i].point.y << " ";

    out << opera_state.radar_set_state.radar_set_state[i].ids.size() << " ";
    std::size_t size_object 
        = opera_state.radar_set_state.radar_set_state[i].ids.size();
    for (std::size_t j=0; j!=size_object; ++j) {
      out << opera_state.radar_set_state.radar_set_state[i].targets[j].x << " "
          << opera_state.radar_set_state.radar_set_state[i].targets[j].y << " "
          << opera_state.radar_set_state.radar_set_state[i].targets_radar[j].x
          << " "
          << opera_state.radar_set_state.radar_set_state[i].targets_radar[j].y
          << " "
          << opera_state.radar_set_state.radar_set_state[i].targets_filter[j].x
          << " "
          << opera_state.radar_set_state.radar_set_state[i].targets_filter[j].y
          << " "
          << opera_state.radar_set_state.radar_set_state[i]
              .targets_angle_azimuth[j]
          << " "
          << opera_state.radar_set_state.radar_set_state[i].ids[j] << " ";
    }
  }
  return out;
}

std::istream& operator>>(std::istream& in,
    Opera2D::OperaState& opera_state) {
  opera_state.track_set_state.track_set_state.clear();
  opera_state.radar_set_state.radar_set_state.clear();
  std::size_t size_track;
  in >> size_track;
  Track2D::TrackState track_state;
  for (std::size_t i=0; i!=size_track; ++i) {
    in >> track_state.id
        >> track_state.point.x
        >> track_state.point.y
        >> track_state.tick
        >> track_state.acc
        >> track_state.speed
        >> track_state.distance
        >> track_state.azimuth;
    opera_state.track_set_state.track_set_state.push_back(track_state);
  }

  Radar2D::RadarState radar_state;
  std::size_t size_radar;
  in >> size_radar;
  for (std::size_t i=0; i!=size_radar; ++i) {
    radar_state.targets.clear();
    radar_state.targets_radar.clear();
    radar_state.targets_filter.clear();
    radar_state.targets_angle_azimuth.clear();
    radar_state.ids.clear();
    
    in >> radar_state.id
        >> radar_state.type
        >> radar_state.point.x
        >> radar_state.point.y;

    Point2D point;
    float angle_azimuth;
    long long id;
    std::size_t size_ids;
    in >> size_ids;
    for (std::size_t j=0; j!=size_ids; ++j) {
      in >> point.x
        >> point.y;
      radar_state.targets.push_back(point);
      in >> point.x
        >> point.y;
      radar_state.targets_radar.push_back(point);
      in >> point.x
        >> point.y;
      radar_state.targets_filter.push_back(point);
      in >> angle_azimuth;
      radar_state.targets_angle_azimuth.push_back(angle_azimuth);
      in >> id;
      radar_state.ids.push_back(id);
    }
    opera_state.radar_set_state.radar_set_state.push_back(radar_state);
  }
  return in;
}

} //namespace tools
