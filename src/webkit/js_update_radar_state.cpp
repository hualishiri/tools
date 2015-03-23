#include "webkit/js_update_radar_state.h"

namespace tools {

std::string JSUpdateRadarState::execute(){
  sstream_ << radar_id_ << ","
           << object_id_;
 std::string js;
  js.append("updateRadarState(");
  js.append(sstream_.str());
  js.append(");");
  sstream_.clear();
  return js;
}

} //namespace tools
