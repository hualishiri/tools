#ifndef TOOLS_OPERA_RADAR_NOISE_H_
#define TOOLS_OPERA_RADAR_NOISE_H_

namespace tools {

class RadarNoise {
 public:
   virtual ~RadarNoise() {}
   virtual void ApplyNoise(double *x,double *y) const = 0;
};

} //namespace tools

#endif //TOOLS_OPERA_RADAR_NOISE_H_
