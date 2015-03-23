#ifndef TOOLS_OPERA_WEBKIT_JS_CREATE_RADAR_STATE_H_
#define TOOLS_OPERA_WEBKIT_JS_CREATE_RADAR_STATE_H_

#include "webkit/js_create_radar_state.h"

namespace tools {

std::string JSCreateRadarState::execute(){
  sstream_ << radar_id_ << ","
           << object_id_;
 std::string js;
  js.append("createRadarState(");
  js.append(sstream_.str());
  js.append(");");
  sstream_.clear();
  return js;
}

} //namespace tools

#endif //TOOLS_OPERA_WEBKIT_JS_CREATE_RADAR_STATE_H_
