#include "webkit/js_update_line.h"

#include "webkit/js_create_line.h"

#include <iomanip>

namespace tools {

std::string JSUpdateLine::execute(){
  sstream_ << line_.id << ","
    << std::setprecision(kPrecision) << line_.start_x << ","
    << std::setprecision(kPrecision) << line_.start_y << ","
    << std::setprecision(kPrecision) << line_.end_x << ","
    << std::setprecision(kPrecision) << line_.end_y;
 std::string js;
  js.append("updateLine(");
  js.append(sstream_.str());
  js.append(");");
  sstream_.clear();
  return js;
}

} //namespace tools
