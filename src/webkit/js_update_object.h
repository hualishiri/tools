#ifndef TOOLS_WEBKIG_JS_UPDATE_OBJECT_H_
#define TOOLS_WEBKIG_JS_UPDATE_OBJECT_H_

#include "webkit/javascript.h"

namespace tools {

struct JSObjectState;

class JSUpdateObject : public  JavaScript {
 public:
  JSUpdateObject(const JSObjectState& state)
    : state_(state) {
  }
  virtual std::string execute();

private:
    const JSObjectState& state_;
};

} //namespace tools

#endif //TOOLS_WEBKIG_JS_UPDATE_OBJECT_H_
