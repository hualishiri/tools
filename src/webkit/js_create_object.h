#ifndef TOOLS_WEBKIG_JS_CREATE_OBJECT_H_
#define TOOLS_WEBKIG_JS_CREATE_OBJECT_H_

#include "webkit/javascript.h"

namespace tools {

struct JSObjectState {
  long long id;
  double x;
  double y;
  double acc;
  double speed;
  double angle;
};

class JSCreateObject : public  JavaScript {
 public:
  JSCreateObject(const JSObjectState& state)
    : state_(state) {
  }
  virtual std::string execute();

private:
    const JSObjectState& state_;
};

} //namespace tools

#endif //TOOLS_WEBKIG_JS_CREATE_OBJECT_H_
