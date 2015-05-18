#include "opera/opera_analysis.h"

namespace tools {

void OperaAnalysis::Handle(const RadarSet2D::RadarSetState& radar_set_state,
                           OperaAnalysisState& opera_analysis_state) {
  OperaAnalysis::OperaAnalysisUnit opera_analysis_unit;

  for (std::size_t i=0;
      i!=radar_set_state.radar_set_state.size();
      ++i) {
    for (std::size_t j=0;
        j!=radar_set_state.radar_set_state[i].ids.size();
        ++j) {
      opera_analysis_unit.radar_id = 
          radar_set_state.radar_set_state[i].id;
      opera_analysis_unit.object_id = 
          radar_set_state.radar_set_state[i].ids[j];

      opera_analysis_unit.error_square = sqrt(pow(
            radar_set_state.radar_set_state[i].targets[j].x
            - radar_set_state.radar_set_state[i].targets_radar[j].x,
            2) + pow(
            radar_set_state.radar_set_state[i].targets[j].y
            - radar_set_state.radar_set_state[i].targets_radar[j].y,
            2));
      opera_analysis_state.track_radar.push_back(opera_analysis_unit);
      
      opera_analysis_unit.error_square = sqrt(pow(
            radar_set_state.radar_set_state[i].targets[j].x
            - radar_set_state.radar_set_state[i].targets_filter[j].x,
            2) + pow(
            radar_set_state.radar_set_state[i].targets[j].y
            - radar_set_state.radar_set_state[i].targets_filter[j].y,
            2));
      opera_analysis_state.track_algorithm.push_back(opera_analysis_unit);
    }
  }
}

} //namespace tools
