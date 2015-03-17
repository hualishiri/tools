#ifndef TOOLS_WEBKIG_JS_CLEAR_LINE_H_
#define TOOLS_WEBKIG_JS_CLEAR_LINE_H_

#include "webkit/javascript.h"

namespace tools {

class JSClearLine : public  JavaScript {
 public:
  virtual std::string execute();
};

} //namespace tools

#endif //TOOLS_WEBKIG_JS_CLEAR_LINE_H_
