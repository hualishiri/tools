#include "data_state_circle.h"

namespace tools {

DataStateCircle* DataStateCircle::Instance() {
  if (!data_) data_ = new DataStateCircle();
  return data_;
}
  
DataStateCircle* DataStateCircle::data_ = 0;

} //namespace tools
