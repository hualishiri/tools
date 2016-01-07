#include "opera/algo_filter_one.h"

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

  tempStr tempstr;

  FilterTarget target;
  for (std::size_t i=0; i!=in->radar_set_state->size(); ++i) {
    if(6 == (*in->radar_set_state)[i].get_type_trival())
      continue;
    for (std::size_t j=0; j!=(*in->radar_set_state)[i].ids.size(); ++j) {
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

        tempstr.TrkDim = 2;
        tempstr.Time = 0;
        tempstr.distance = (*in->radar_set_state)[i].targets_detected_distance[j];
        tempstr.bearing = (*in->radar_set_state)[i].targets_detected_azimuth[j];
        tempstr.elevation = (*in->radar_set_state)[i].targets_detected_elevation[j];
        tempstr.speed = (*in->radar_set_state)[i].targets_detected_velocity[j];
        tempstr.course = (*in->radar_set_state)[i].targets_detected_course[j];

        Convert2Degree(tempstr);
        Dofiltering(tempstr);
        Convert2Radius(tempstr);
        
        target.filter_azimuth = tempstr.bearing; 
        target.filter_distance = tempstr.distance;
        target.filter_elevation = tempstr.elevation;
        target.filter_velocity = tempstr.speed;
        target.filter_course = tempstr.course;

        target.radar_ids.clear();
        target.radar_ids.push_back((*in->radar_set_state)[i].id);

        CalculateFilterError(target);

        out->targets->push_back(target);
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
