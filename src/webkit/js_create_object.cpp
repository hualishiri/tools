#include "webkit/js_create_object.h"

#include <iomanip>

namespace tools {

std::string JSCreateObject::execute(){
 sstream_ << state_.id << ","
          << std::setprecision(kPrecision) << state_.x << ","
          << std::setprecision(kPrecision) << state_.y << ","
          << state_.acc << ","
          << state_.speed << ","
          << state_.angle;
 std::string js;
 js.append("createObject(");
 js.append(sstream_.str());
 js.append(");");
 sstream_.clear();
 return js;
}

} //namespace tools
