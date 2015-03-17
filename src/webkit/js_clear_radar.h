#ifndef TOOLS_WEBKIG_JS_CLEAR_RADAR_H_
#define TOOLS_WEBKIG_JS_CLEAR_RADAR_H_

#include "webkit/javascript.h"

namespace tools {

struct JSRadar;

class JSClearRadar : public  JavaScript {
 public:
  virtual std::string execute();
};

} //namespace tools

#endif //TOOLS_WEBKIG_JS_CLEAR_RADAR_H_
