#include "data_state_line.h"

namespace tools {

DataStateLine* DataStateLine::Instance() {
  if (!data_) data_ = new DataStateLine();
  return data_;
}

DataStateLine* DataStateLine::data_ = 0;

} //namespace tools
