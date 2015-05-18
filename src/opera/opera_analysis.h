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
    double error_square;
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
