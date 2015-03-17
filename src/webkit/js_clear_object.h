#ifndef TOOLS_WEBKIG_JS_CLEAR_OBJECT_H_
#define TOOLS_WEBKIG_JS_CLEAR_OBJECT_H_

#include "webkit/javascript.h"

namespace tools {

class JSClearObject : public  JavaScript {
 public:
  virtual std::string execute();
};

} //namespace tools

#endif //TOOLS_WEBKIG_JS_CLEAR_OBJECT_H_
