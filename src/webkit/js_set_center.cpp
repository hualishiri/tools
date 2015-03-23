#include "webkit/js_set_center.h"

#include <assert.h>
#include <iomanip>

namespace tools {

std::string JSSetCenter::execute(){
  assert(longitude_ > -180.0 && longitude_ < 180.0);
  assert(latitude_ > -90.0 && latitude_ < 90.0);
  sstream_ << std::setprecision(kPrecision) << longitude_ << ","
    << std::setprecision(kPrecision) << latitude_;
  std::string js;
  js.append("setCenter(");
  js.append(sstream_.str());
  js.append(");");
  sstream_.clear();
  return js;
}

} //namespace tools
