#ifndef TOOLS_OPERA_ALGO_FILTER_
#define TOOLS_OPERA_ALGO_FILTER_

#include "opera/algorithm.h"
#include "opera/radar.h"

namespace tools {

class AlgoFilter : public Algorithm {
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

  struct FilterTarget {
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

    Point2D filter_position;
    double filter_height;
    double filter_azimuth;
    double filter_distance;
    double filter_elevation;
    double filter_velocity;
    double filter_course;

    TargetError filter_error;
  };

  struct Input {
    std::vector<Radar2D::RadarState> *radar_set_state;
  };

  struct Output {
    std::vector<FilterTarget> *targets;
  };

  void Handle(void* input, void* output);
  void CalculateFilterError(FilterTarget& filter_target) const;
};

} //namespace tools

#endif //TOOLS_OPERA_FILTER_
