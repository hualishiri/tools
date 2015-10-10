#include "opera/algo_filter.h"

#include <stddef.h>

#include <map>

namespace tools {

struct StatisticsTarget {
  struct AlgoFilter::FilterTarget target;
  int count;
};

void AlgoFilter::Handle(void* input, void* output) {
  if (NULL == input || NULL == output)
    return;
  Input* in = (Input*) input;
  Output* out = (Output*) output;
  out->targets->clear();

  FilterTarget target;
  std::map<long long, StatisticsTarget> statistics; 
  for (std::size_t i=0; i!=in->radar_set_state->size(); ++i) {
    if(6 == (*in->radar_set_state)[i].get_type_trival())
      continue;
    for (std::size_t j=0; j!=(*in->radar_set_state)[i].ids.size(); ++j) {
      std::size_t count = statistics.count((*in->radar_set_state)[i].ids[j]);
      if (0 == count ) {
        target.id_target = (*in->radar_set_state)[i].ids[j];
        target.real_position.x = 
            (*in->radar_set_state)[i].targets[j].x;
        target.real_position.y = 
            (*in->radar_set_state)[i].targets[j].y;
        target.real_height = (*in->radar_set_state)[i].targets_height[j];
        target.real_azimuth = (*in->radar_set_state)[i].targets_angle_azimuth[j];
        target.real_distance = (*in->radar_set_state)[i].targets_real_distance[j];
        target.real_elevation = (*in->radar_set_state)[i].targets_real_elevation[j];
        target.real_velocity = (*in->radar_set_state)[i].targets_real_velocity[j];
        target.real_course = (*in->radar_set_state)[i].targets_real_course[j];
        target.filter_position.x = (*in->radar_set_state)[i].targets_radar[j].x;
        target.filter_position.y = (*in->radar_set_state)[i].targets_radar[j].y;
        target.filter_height = (*in->radar_set_state)[i].targets_radar_height[j];
        target.filter_azimuth = (*in->radar_set_state)[i].targets_detected_azimuth[j];
        target.filter_distance = (*in->radar_set_state)[i].targets_detected_distance[j];
        target.filter_elevation = (*in->radar_set_state)[i].targets_detected_elevation[j];
        target.filter_velocity = (*in->radar_set_state)[i].targets_detected_velocity[j];
        target.filter_course = (*in->radar_set_state)[i].targets_detected_course[j];
        target.radar_ids.clear();
        target.radar_ids.push_back((*in->radar_set_state)[i].id);

        StatisticsTarget temp;
        temp.count = 1;
        temp.target = target;
        statistics.insert(std::make_pair((*in->radar_set_state)[i].ids[j],
            temp));
      } if ( (*in->radar_set_state)[i].ids[j] % 2 != 0){
        target.id_target = (*in->radar_set_state)[i].ids[j];
        statistics[target.id_target].target.filter_position.x +=
            (*in->radar_set_state)[i].targets_radar[j].x;
        statistics[target.id_target].target.filter_position.y +=
            (*in->radar_set_state)[i].targets_radar[j].y;
        statistics[target.id_target].target.filter_height
            += (*in->radar_set_state)[i].targets_radar_height[j];
        statistics[target.id_target].target.filter_azimuth 
            += (*in->radar_set_state)[i].targets_detected_azimuth[j];
        statistics[target.id_target].target.filter_distance 
            += (*in->radar_set_state)[i].targets_detected_distance[j];
        statistics[target.id_target].target.filter_elevation 
            += (*in->radar_set_state)[i].targets_detected_elevation[j];
        statistics[target.id_target].target.filter_velocity 
            += (*in->radar_set_state)[i].targets_detected_velocity[j];
        statistics[target.id_target].target.filter_course
            += (*in->radar_set_state)[i].targets_detected_course[j];
        statistics[target.id_target].target.radar_ids.push_back(
            (*in->radar_set_state)[i].id);
        ++statistics[target.id_target].count;
      }
    }
  }

  int count = 0;
  int i = 0;
  for (std::map<long long, StatisticsTarget>::iterator iter = statistics.begin();
      iter != statistics.end(); ++iter) {
    count = iter->second.count;
    if (1 != count) {
      target = iter->second.target; 
      target.filter_position.x /= count;
      target.filter_position.y /= count;
      target.filter_height /= count;
      target.filter_azimuth /= count;
      target.filter_distance /= count;
      target.filter_elevation /= count;
      target.filter_velocity /= count;
      target.filter_course /= count;
      CalculateFilterError(target);
      target.filter_error.accuracy_association = 
        1.0 * count / (count + i);
      out->targets->push_back(target);
      ++i;
    }
  }
}

void AlgoFilter::CalculateFilterError(FilterTarget& filter_target) const {
  filter_target.filter_error.error_rela_distance = 
      filter_target.filter_distance - filter_target.real_distance;
  filter_target.filter_error.error_rela_azimuth =
      filter_target.filter_azimuth - filter_target.real_azimuth;
  filter_target.filter_error.error_rela_elevation =
      filter_target.filter_elevation - filter_target.real_elevation;

  filter_target.filter_error.error_rela_space = sqrt(
      pow(filter_target.real_position.x - filter_target.filter_position.x,2) + 
      pow(filter_target.real_position.y - filter_target.filter_position.y,2));
  filter_target.filter_error.error_rela_velocity =
      filter_target.filter_velocity - filter_target.real_velocity;
  filter_target.filter_error.error_rela_course =
      filter_target.filter_course - filter_target.real_course;
}

} //namespace tools 
