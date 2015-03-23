#include "webkit/js_delete_radar.h"

namespace tools {

std::string JSDeleteRadar::execute(){
 sstream_ << id_;
 std::string js;
 js.append("deleteRadar(");
 js.append(sstream_.str());
 js.append(");");
 sstream_.clear();
  return js;
}

} //namespace tools
