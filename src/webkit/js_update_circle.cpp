#include "webkit/js_update_circle.h"

#include <iomanip>

#include "webkit/js_create_circle.h"

namespace tools {

std::string JSUpdateCircle::execute(){
  sstream_ << circle_.id << ","
    << std::setprecision(kPrecision) << circle_.start_x << ","
    << std::setprecision(kPrecision) << circle_.start_y << ","
    << std::setprecision(kPrecision) << circle_.radius_x<< ","
    << std::setprecision(kPrecision) << circle_.radius_y<< ","
    << circle_.angle;
 std::string js;
  js.append("updateCircle(");
  js.append(sstream_.str());
  js.append(");");
  sstream_.clear();
  return js;
}

} //namespace tools
