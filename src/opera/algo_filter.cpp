#include "opera/algo_filter.h"

namespace tools {

void AlgoFilter::Handle(void* input, void* output) {
  Input* in = (Input*)input;
  Input temp = *in;
  temp.distance *= (1 + 0.001);
  temp.azimuth *= (1 + 0.001);
  temp.elevation *= (1 + 0.001);
  temp.speed *= (1 + 0.001);
  temp.direction *= (1 + 0.001);
  
  Output* out = (Output*)output;
  
  out->diemonsion = temp.diemonsion;
  out->time = temp.time;
  out->distance = temp.distance;
  out->azimuth = temp.azimuth;
  out->elevation = temp.elevation;
  out->speed = temp.speed;
  out->direction = temp.direction;
}

} //namespace tools 
