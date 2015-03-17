#ifndef TOOLS_WEBKIG_JS_UPDATE_RADAR_H_
#define TOOLS_WEBKIG_JS_UPDATE_RADAR_H_

#include "webkit/javascript.h"

namespace tools {

struct JSRadar;

class JSUpdateRadar : public  JavaScript {
 public:
  JSUpdateRadar(const JSRadarState& state)
    : state_(state) {
  }
  virtual std::string execute();

private:
    const JSRadarState& state_;
};

} //namespace tools

#endif //TOOLS_WEBKIG_JS_UPDATE_RADAR_H_
