#include "webkit/js_update_object.h"

#include <iomanip>

#include "webkit/js_create_object.h"

namespace tools {

std::string JSUpdateObject::execute() {
 sstream_ << state_.id << ","
          << std::setprecision(kPrecision) << state_.x << ","
          << std::setprecision(kPrecision) << state_.y << ","
          << state_.acc << ","
          << state_.speed << ","
          << state_.angle;
 std::string js;
 js.append("updateObject(");
 js.append(sstream_.str());
 js.append(");");
 sstream_.clear();
  return js;
}

} //namespace tools
