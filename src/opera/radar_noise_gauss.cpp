#include "opera/radar_noise_gauss.h"

#include "util/logger.h"
#include "util/tool.h"

namespace tools {

void RadarNoiseGauss::ApplyNoise(double* x, double* y) const{
  double x_temp = *x + level_noise_ / 156.54 
      * GetRandNumber(static_cast<int>(*x));
  double y_temp = *y + level_noise_ / 156.54 
      * GetRandNumber(*y);
  if (x_temp < 0.0 && x_temp > 256.0)
    x_temp = *x;
  if (y_temp < 0.0 && y_temp > 256.0)
    y_temp = *y;
  *x = x_temp;
  *y = y_temp;
}

} //namespace tools
