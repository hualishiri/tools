#include "webkit/js_delete_radar_state.h"

namespace tools {

std::string JSDeleteRadarState::execute(){
  sstream_ << radar_id_ << ","
           << object_id_;
 std::string js;
  js.append("deleteRadarState(");
  js.append(sstream_.str());
  js.append(");");
  sstream_.clear();
  return js;
}

} //namespace tools
