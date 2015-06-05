#ifndef TOOLS_OPERA_ANALYSIS_H_
#define TOOLS_OPERA_ANALYSIS_H_

#include <vector>

#include "opera/radar_set.h"

namespace tools {

class OperaAnalysis {
 public:
  struct OperaAnalysisUnit {
    long long radar_id;
    long long object_id;
    double error_system_distance;
    double error_system_azimuth;
    double error_system_elevation;
    double error_random_distance;
    double error_random_azimuth;
    double error_random_elevation;
    double error_overall_distance;
    double error_overall_azimuth;
    double error_overall_elevation;
    double error_space;
    double error_velocity;
    double error_distance;
  };

  struct OperaAnalysisState {
    std::vector<OperaAnalysisUnit> track_radar;
    std::vector<OperaAnalysisUnit> track_algorithm;
  };

  static void Handle(const RadarSet2D::RadarSetState& radar_set_state,
              OperaAnalysisState& opera_analysis_state);

};

} //namespace t ools

#endif //TOOLS_OPERA_ANALYSIS_H_
