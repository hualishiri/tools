#include "opera/algo_fusion.h"

#include <stddef.h>

#include <map>

namespace tools {

struct StatisticsTarget {
  struct AlgoFusion::FusionTarget target;
  int count;
};

void AlgoFusion::Handle(void* input, void* output) {
  if (NULL == input || NULL == output)
    return;
  Input* in = (Input*) input;
  Output* out = (Output*) output;
  out->targets->clear();

  FusionTarget target;
  std::map<long long, StatisticsTarget> statistics; 
  for (std::size_t i=0; i!=in->radar_set_state->size(); ++i) {
    if(6 == (*in->radar_set_state)[i].get_type_trival())
      continue;
    for (std::size_t j=0; j!=(*in->radar_set_state)[i].ids.size(); ++j) {
      if (0 == statistics.count((*in->radar_set_state)[i].ids[j])) {
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
        target.fusion_position.x = (*in->radar_set_state)[i].targets_radar[j].x;
        target.fusion_position.y = (*in->radar_set_state)[i].targets_radar[j].y;
        target.fusion_height = (*in->radar_set_state)[i].targets_radar_height[j];
        target.fusion_azimuth = (*in->radar_set_state)[i].targets_detected_azimuth[j];
        target.fusion_distance = (*in->radar_set_state)[i].targets_detected_distance[j];
        target.fusion_elevation = (*in->radar_set_state)[i].targets_detected_elevation[j];
        target.fusion_velocity = (*in->radar_set_state)[i].targets_detected_velocity[j];
        target.fusion_course = (*in->radar_set_state)[i].targets_detected_course[j];
        target.radar_ids.clear();
        target.radar_ids.push_back((*in->radar_set_state)[i].id);

        StatisticsTarget temp;
        temp.count = 1;
        temp.target = target;
        statistics.insert(std::make_pair((*in->radar_set_state)[i].ids[j],
            temp));
      } else {
        target.id_target = (*in->radar_set_state)[i].ids[j];
        statistics[target.id_target].target.fusion_position.x +=
            (*in->radar_set_state)[i].targets_radar[j].x;
        statistics[target.id_target].target.fusion_position.y +=
            (*in->radar_set_state)[i].targets_radar[j].y;
        statistics[target.id_target].target.fusion_height
            += (*in->radar_set_state)[i].targets_radar_height[j];
        statistics[target.id_target].target.fusion_azimuth 
            += (*in->radar_set_state)[i].targets_detected_azimuth[j];
        statistics[target.id_target].target.fusion_distance 
            += (*in->radar_set_state)[i].targets_detected_distance[j];
        statistics[target.id_target].target.fusion_elevation 
            += (*in->radar_set_state)[i].targets_detected_elevation[j];
        statistics[target.id_target].target.fusion_velocity 
            += (*in->radar_set_state)[i].targets_detected_velocity[j];
        statistics[target.id_target].target.fusion_course
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
      target.fusion_position.x /= count;
      target.fusion_position.y /= count;
      target.fusion_height /= count;
      target.fusion_azimuth /= count;
      target.fusion_distance /= count;
      target.fusion_elevation /= count;
      target.fusion_velocity /= count;
      target.fusion_course /= count;
      CalculateFusionError(target);
      target.fusion_error.accuracy_association = 
        1.0 * count / (count + i);
      out->targets->push_back(target);
      ++i;
    }
  }
}

void AlgoFusion::CalculateFusionError(FusionTarget& fusion_target) const {
  fusion_target.fusion_error.error_rela_distance = 
      fusion_target.fusion_distance - fusion_target.real_distance;
  fusion_target.fusion_error.error_rela_azimuth =
      fusion_target.fusion_azimuth - fusion_target.real_azimuth;
  fusion_target.fusion_error.error_rela_elevation =
      fusion_target.fusion_elevation - fusion_target.real_elevation;

  fusion_target.fusion_error.error_rela_space = sqrt(
      pow(fusion_target.real_position.x - fusion_target.fusion_position.x,2) + 
      pow(fusion_target.real_position.y - fusion_target.fusion_position.y,2));
  fusion_target.fusion_error.error_rela_velocity =
      fusion_target.fusion_velocity - fusion_target.real_velocity;
  fusion_target.fusion_error.error_rela_course =
      fusion_target.fusion_course - fusion_target.real_course;
}

} //namespace tools
