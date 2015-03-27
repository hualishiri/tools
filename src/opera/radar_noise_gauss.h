#ifndef TOOLS_OPERA_RADAR_NOISE_GAUSS_H_
#define TOOLS_OPERA_RADAR_NOISE_GAUSS_H_

#include "opera/radar_noise.h"

namespace tools {

class RadarNoiseGauss : public RadarNoise {
 public:
   RadarNoiseGauss(double level_nosie) : level_noise_(level_nosie) {}

   virtual void ApplyNoise(double* x, double* y) const;

 private:
   double level_noise_;
};

} //namespace tools

#endif //TOOLS_OPERA_RADAR_NOISE_GAUSS_H_
