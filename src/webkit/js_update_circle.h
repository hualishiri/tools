#ifndef TOOLS_OPERA_WEBKIT_JS_UPDATE_CIRCLE_H_
#define TOOLS_OPERA_WEBKIT_JS_UPDATE_CIRCLE_H_

#include "webkit/javascript.h"
#include "webkit/js_create_circle.h"

namespace tools {

class JSUpdateCircle : public JavaScript {
 public:
  JSUpdateCircle(const JSCircle& circle) : circle_(circle) {}
  virtual std::string execute();

 private:
  const JSCircle& circle_;
};

} //namespace tools

#endif //TOOLS_OPERA_WEBKIT_JS_UPDATE_CIRCLE_H_
