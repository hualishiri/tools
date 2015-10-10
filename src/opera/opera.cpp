#include "opera/opera.h"

#include <assert.h>

#include <vector>
#include <iomanip>

#include "opera/acceleration.h"
#include "opera/circle.h"
#include "opera/algo_fusion.h"
#include "opera/algo_filter.h"
#include "opera/line.h"
#include "opera/opera_option.h"
#include "opera/radar_sector.h"
#include "opera/radar_noise_gauss.h"
#include "util/tool.h"

namespace tools {

void Opera2D::Initialize(const OperaOption& opera_option) {
  BuildRadar(opera_option);
  BuildTrack(opera_option);
}

void Opera2D::BuildRadar(const OperaOption& opera_option) {
  RadarSet2D::RadarSet* rep_radar_set = new RadarSet2D::RadarSet();
  garbage_.garbage_radar_set2d_radar_sets.push_back(rep_radar_set);
  std::vector<OperaOption::Radar> radars = opera_option.radars();
  for (std::size_t i = 0; i != radars.size(); ++i) {
    SectorRadar::Radar* radar = new SectorRadar::Radar();
    garbage_.garbage_sector_radar_radars.push_back(radar);
    radar->id = radars[i].id;
    radar->type = radars[i].type;
    if (radars[i].type == OperaOption::R_STATIC) {
      radar->track_id = 0;
    } 
    if (radars[i].type == OperaOption::R_DYNAMIC) {
      radar->track_id = radars[i].track_id;
    }
    radar->x = radars[i].radius_x;
    radar->y = radars[i].radius_y;
    radar->height = radars[i].height;
    radar->azimuth_range = radars[i].azimuth_range;

    radar->distance_detect = Distance2D(radars[i].start_x,
                                           radars[i].start_y,
                                           radars[i].radius_x,
                                           radars[i].radius_y);

    //radar->level_noise = radars[i].level_noise;
    radar->error_random_distance = radars[i].error.error_random_distance;
    radar->error_random_azimuth = radars[i].error.error_random_azimuth;
    radar->error_random_elevation = radars[i].error.error_random_elevation;
    radar->error_system_distance = radars[i].error.error_system_distance;
    radar->error_system_azimuth = radars[i].error.error_system_azimuth;
    radar->error_system_elevation = radars[i].error.error_system_elevation;

    radar->detecting_objects_types = radars[i].detecting_objects_types;
    RadarNoise* radar_noise = new RadarNoiseGauss(radar->level_noise);
    garbage_.garbage_radar_noises.push_back(radar_noise);
    SectorRadar* sector_radar = new SectorRadar(radar, radar_noise);
    garbage_.garbage_sector_radars.push_back(sector_radar);
    rep_radar_set->push_back(sector_radar);
  }
  radar_set_ = new RadarSet2D(rep_radar_set);
}

void Opera2D::BuildTrack(const OperaOption& opera_option) {
  TrackSet2D::TrackSet *track_set_rep = new TrackSet2D::TrackSet();
  garbage_.garbage_track_set2d_track_sets.push_back(track_set_rep);
  std::vector<OperaOption::TrackInternal> tracks
       = opera_option.tracks();
  std::vector<OperaOption::TrackUnitType> tracks_type;
  TrackSet2D::TrackSetPosition* track_set_position
       = new TrackSet2D::TrackSetPosition();;
  garbage_.garbage_track_set2d_track_set_positions.push_back(track_set_position);
  double old_speed = 0.0;
  double current_speed = 0.0;
  TrackSet2D::TrackSetDelay* track_set_delay = new TrackSet2D::TrackSetDelay();
  garbage_.garbage_track_set2d_track_set_delays.push_back(track_set_delay);
  for(std::size_t i=0; i != tracks.size(); ++i) {
    track_set_delay->push_back(tracks[i].time_delay / opera_option.interval());
    Track2D::TrackUnitSet* track_unit_set = new Track2D::TrackUnitSet();
    garbage_.garbage_track2d_track_unit_sets.push_back(track_unit_set);
    int index_line = 0;
    int index_circle = 0;
    Point2D* point = NULL;
    for (std::size_t j = 0; j != tracks[i].types.size(); ++j) {
      Shape2D* shape = 0;
      if (tracks[i].types[j] == OperaOption::LINE) {
        if (j == 0) {
          point = new Point2D(tracks[i].lines[index_line].start_x,
                              tracks[i].lines[index_line].start_y);
          garbage_.garbage_points.push_back(point);
          track_set_position->push_back(point);
        }
        shape = new Line2D(Point2D(
            tracks[i].lines[index_line].end_x
            - tracks[i].lines[index_line].start_x,
            tracks[i].lines[index_line].end_y 
            - tracks[i].lines[index_line].start_y));
        garbage_.garbage_shapes.push_back(shape);
        ++index_line;
      } else if (tracks[i].types[j] == OperaOption::CIRCLE) {
        if (j == 0) {
          point = new Point2D(tracks[i].circles[index_circle].start_x,
                              tracks[i].circles[index_circle].start_y);
          garbage_.garbage_points.push_back(point);
          track_set_position->push_back(point);
        }
        shape = new Circle2D(Point2D(
            tracks[i].circles[index_circle].center_x
            - tracks[i].circles[index_circle].start_x,
            tracks[i].circles[index_circle].center_y
            - tracks[i].circles[index_circle].start_y),
            tracks[i].circles[index_circle].angle);
        garbage_.garbage_shapes.push_back(shape);
        ++index_circle;
      }
      Acceleration* acc_uniform = new ConstantAcceleration(
          tracks[i].acceleration[j]);
      garbage_.garbage_accelerations.push_back(acc_uniform);
      if (0 == j)
       current_speed = tracks[i].start_speed;
     else
       current_speed = old_speed; 
     assert(0 != shape);
     TrackUnit* track_unit = new TrackUnit(shape,
                                           acc_uniform,
                                           opera_option.interval(),
                                           current_speed);
     garbage_.garbage_track_units.push_back(track_unit);
      old_speed = track_unit->GetEndSpeed();
      track_unit_set->push_back(track_unit);
    }
    Track2D* track = new Track2D(tracks[i].id,
        track_unit_set,
        opera_option.interval(),
        tracks[i].start_speed,
        tracks[i].height);
    garbage_.garbage_track2ds.push_back(track);
    track->set_track_type(tracks[i].track_type);
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
  if (track_set_) {
    delete track_set_;
    track_set_ = NULL;
  }
  if (radar_set_) {
    delete radar_set_;
    radar_set_ = NULL;
  }
  for (std::size_t i=0; i!=garbage_.garbage_radar_set2d_radar_sets.size(); ++i)
    delete garbage_.garbage_radar_set2d_radar_sets[i];
  garbage_.garbage_radar_set2d_radar_sets.clear();
  
  for (std::size_t i=0; i!=garbage_.garbage_sector_radar_radars.size(); ++i)
    delete garbage_.garbage_sector_radar_radars[i];
  garbage_.garbage_sector_radar_radars.clear();

  for (std::size_t i=0; i!=garbage_.garbage_radar_noises.size(); ++i)
    delete garbage_.garbage_radar_noises[i];
  garbage_.garbage_radar_noises.clear();

  for (std::size_t i=0; i!=garbage_.garbage_sector_radars.size(); ++i)
    delete garbage_.garbage_sector_radars[i];
  garbage_.garbage_sector_radars.clear();

  for (std::size_t i=0; i!=garbage_.garbage_track_set2d_track_sets.size(); ++i)
    delete garbage_.garbage_track_set2d_track_sets[i];
  garbage_.garbage_track_set2d_track_sets.clear();

  for (std::size_t i=0;
      i!=garbage_.garbage_track_set2d_track_set_positions.size();
      ++i)
    delete garbage_.garbage_track_set2d_track_set_positions[i];
  garbage_.garbage_track_set2d_track_set_positions.clear();

  for (std::size_t i=0;
      i!=garbage_.garbage_track_set2d_track_set_delays.size();
      ++i)
    delete garbage_.garbage_track_set2d_track_set_delays[i];
  garbage_.garbage_track_set2d_track_set_delays.clear();

  for (std::size_t i=0; i!=garbage_.garbage_track2d_track_unit_sets.size(); ++i)
    delete garbage_.garbage_track2d_track_unit_sets[i];
  garbage_.garbage_track2d_track_unit_sets.clear();

  for (std::size_t i=0; i!=garbage_.garbage_points.size(); ++i)
    delete garbage_.garbage_points[i];
  garbage_.garbage_points.clear();

  for (std::size_t i=0; i!=garbage_.garbage_shapes.size(); ++i)
    delete garbage_.garbage_shapes[i];
  garbage_.garbage_shapes.clear();

  for (std::size_t i=0; i!=garbage_.garbage_accelerations.size(); ++i)
    delete garbage_.garbage_accelerations[i];
  garbage_.garbage_accelerations.clear();

  for (std::size_t i=0; i!=garbage_.garbage_track_units.size(); ++i)
    delete garbage_.garbage_track_units[i];
  garbage_.garbage_track_units.clear();

  for (std::size_t i=0; i!=garbage_.garbage_track2ds.size(); ++i)
    delete garbage_.garbage_track2ds[i];
  garbage_.garbage_track2ds.clear();
}

long long Opera2D::GetSumTick() const {
  return track_set_->GetSumTick();
}

Opera2D::Iterator::Iterator(Opera2D* opera) {
  opera_ = opera;
  iter_track_set_ = new TrackSet2D::Iterator(opera_->track_set_);
}

Opera2D::Iterator::Iterator(const Iterator& iterator) {
  opera_ = iterator.opera_;
  iter_track_set_ = new TrackSet2D::Iterator(opera_->track_set_);
  *iter_track_set_ = *(iterator.iter_track_set_); 
}

Opera2D::Iterator& Opera2D::Iterator::operator=(const Iterator& iterator) {
  opera_ = iterator.opera_;
  if (iter_track_set_) {
    delete iter_track_set_;
    iter_track_set_ = NULL;
  }
  iter_track_set_ = new TrackSet2D::Iterator(opera_->track_set_);
  *iter_track_set_ = *(iterator.iter_track_set_); 
  return *this;
}

Opera2D::Iterator::~Iterator() {
  if (iter_track_set_) {
    delete iter_track_set_;
    iter_track_set_ = NULL;
  }
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
  AlgoFusion algo_fusion;
  AlgoFusion::Input input; 
  AlgoFusion::Output output;
  input.radar_set_state = &opera_state.radar_set_state.radar_set_state;
  output.targets = &opera_state.fusion_set_state;
  algo_fusion.Handle((void*)&input, (void*)&output);

  AlgoFilter algo_filter;
  AlgoFilter::Input filter_input; 
  AlgoFilter::Output filter_output;
  filter_input.radar_set_state = &opera_state.radar_set_state.radar_set_state;
  filter_output.targets = &opera_state.filter_set_state;
  algo_filter.Handle((void*)&filter_input, (void*)&filter_output);


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

void Opera2D::OperaState::ConvertToWgs(void (*Conv)(double*, double*)) {
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
    // 1 refer to a shipbased radar
    if ((*(opera_->radar_set_->radar_set()))[i]->type() == 1) {
      for (std::size_t j=0; j!=size_track; ++j) {
        if ((*(opera_->radar_set_->radar_set()))[i]->track_id() 
            == opera_state.track_set_state.track_set_state[j].id) {
          (*(opera_->radar_set_->radar_set()))[i]->SetPosition(
              opera_state.track_set_state.track_set_state[j].point.x,
              opera_state.track_set_state.track_set_state[j].point.y);
        }
      }
    }

  }
}

std::ostream& operator<<(std::ostream& out,
                         const Opera2D::OperaState& opera_state) {
  out << std::fixed << std::setprecision(20);
  out << opera_state.track_set_state << " ";
  out << opera_state.radar_set_state << " ";
  return out;
}

std::istream& operator>>(std::istream& in,
    Opera2D::OperaState& opera_state) {
  in >> opera_state.track_set_state;
  in >> opera_state.radar_set_state;
  return in;
}

} //namespace tools
