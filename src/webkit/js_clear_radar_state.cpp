#include "webkit/js_clear_radar_state.h"

namespace tools {

std::string JSClearRadarState::execute(){
  sstream_ << radar_id_;
 std::string js;
  js.append("clearRadarState(");
  js.append(sstream_.str());
  js.append(");");
  sstream_.clear();
  return js;
}

} //namespace tools


