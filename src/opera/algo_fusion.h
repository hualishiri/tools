#ifndef TOOLS_OPERA_ALGO_FUSION_
#define TOOLS_OPERA_ALGO_FUSION_

#include "opera/algorithm.h"
#include "opera/radar.h"

namespace tools {

class AlgoFusion : public Algorithm {
public:
  struct TargetError {
    double error_abs_distance;
    double error_abs_azimuth;
    double error_abs_elevation;
    double error_abs_velocity;

    double error_rms_distance;
    double error_rms_azimuth;
    double error_rms_elevation;
    double error_rms_velocity;

    double error_rela_distance;
    double error_rela_azimuth;
    double error_rela_elevation;
    double error_rela_velocity;

    double accuracy_association;
  };

  struct FusionTarget {
    long long id_target;

    Point2D real_position;
    double real_azimuth;
    double real_distance;
    double real_elevation;
    double real_velocity;

    Point2D fusion_position;
    double fusion_azimuth;
    double fusion_distance;
    double fusion_elevation;
    double fusion_velocity;

    TargetError fusion_error;
  };

  struct Input {
    std::vector<Radar2D::RadarState> *radar_set_state;
  };

  struct Output {
    std::vector<FusionTarget> *targets;
  };

  void Handle(void* input, void* output);
  void CalculateFusionError(FusionTarget& fusion_target) const;
};

} //namespace tools

#endif //TOOLS_OPERA_FUSION_
