#include "opera/radar_noise_gauss.h"

#include "util/logger.h"
#include "util/testharness.h"

namespace tools {

class RADARNOISEGAUSS {};

TEST(RADARNOISEGAUSS, ApplyNoise) {
  double x = 20;
  double y = 30;
  RadarNoise* radar_noise = new RadarNoiseGauss(156);
  radar_noise->ApplyNoise(&x, &y);
}

} //namespace tools

int main(int argc, char** argv) {
  return tools::test::RunAllTests();
}
