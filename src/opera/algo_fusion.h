#ifndef TOOLS_OPERA_ALGO_FUSION_
#define TOOLS_OPERA_ALGO_FUSION_

#include "opera/algorithm.h"
#include "opera/radar.h"

namespace tools {

class AlgoFusion : public Algorithm {
public:
  struct TargetError {
    double error_rela_distance;
    double error_rela_azimuth;
    double error_rela_elevation;

    double error_rela_space;
    double error_rela_velocity;
    double error_rela_course;

    double accuracy_association;
  };

  struct FusionTarget {
    long long tick;
    long long id_target;

    std::vector<long long> radar_ids;

    Point2D real_position;
    double real_height;
    double real_azimuth;
    double real_distance;
    double real_elevation;
    double real_velocity;
    double real_course;

    Point2D fusion_position;
    double fusion_height;
    double fusion_azimuth;
    double fusion_distance;
    double fusion_elevation;
    double fusion_velocity;
    double fusion_course;

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
