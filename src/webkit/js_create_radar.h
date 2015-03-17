#ifndef TOOLS_WEBKIG_JS_CREATE_RADAR_H_
#define TOOLS_WEBKIG_JS_CREATE_RADAR_H_

#include "webkit/javascript.h"

namespace tools {

struct JSRadar{
  long long id;
  int type;
  double center_x;
  double center_y;
  double radius;
};

class JSCreateRadar : public  JavaScript {
 public:
  JSCreateRadar(const JSRadarState& state)
    : state_(state) {
  }
  virtual std::string execute();

private:
    const JSRadarState& state_;
};

} //namespace tools

#endif //TOOLS_WEBKIG_JS_CREATE_RADAR_H_
