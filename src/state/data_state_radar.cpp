#include "data_state_radar.h"

namespace tools {

DataStateRadar* DataStateRadar::Instance() {
  if (!data_) data_ = new DataStateRadar();
  return data_;
}

DataStateRadar* DataStateRadar::data_ = 0;

} //namespace tools
