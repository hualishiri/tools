#ifndef TOOLS_OPERA_ALGO_FILTER_
#define TOOLS_OPERA_ALGO_FILTER_

#include "opera/algorithm.h"

namespace tools {

class AlgoFilter : public Algorithm {
public:
  struct Input {
    int diemonsion;
    long long time;
    double distance;
    double azimuth;
    double elevation;
    double speed;
    double direction;
  };

  struct Output {
    int diemonsion;
    long long time;
    double distance;
    double azimuth;
    double elevation;
    double speed;
    double direction;
  };

  virtual void Handle(void* input, void* output);
};

} //namespace tools

#endif //TOOLS_OPERA_FILTER_
