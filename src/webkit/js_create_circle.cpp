#include "webkit/js_create_circle.h"

#include <iomanip>

namespace tools {

std::string JSCreateCircle::execute(){
  sstream_ << circle_.id << ","
    << std::setprecision(kPrecision) << circle_.start_x << ","
    << std::setprecision(kPrecision) << circle_.start_y << ","
    << std::setprecision(kPrecision) << circle_.radius_x<< ","
    << std::setprecision(kPrecision) << circle_.radius_y<< ","
    << circle_.angle;
 std::string js;
  js.append("createCircle(");
  js.append(sstream_.str());
  js.append(");");
  sstream_.clear();
  return js;
}

} //namespace tools
