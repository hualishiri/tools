#include "webkit/js_update_radar.h"

#include <iomanip>

#include "webkit/js_create_radar.h"

namespace tools {

std::string JSUpdateRadar::execute(){
  sstream_ << state_.id << ","
           << state_.type << ","
           << std::setprecision(kPrecision) << state_.center_x << ","
           << std::setprecision(kPrecision) << state_.center_y << ","
           << std::setprecision(kPrecision) << state_.radius;
 std::string js;
  js.append("updateRadar(");
  js.append(sstream_.str());
  js.append(");");
  sstream_.clear();
  return js;
}

} //namespace tools
