#ifndef TOOLS_WEBKIG_JS_DELETE_LINE_H_
#define TOOLS_WEBKIG_JS_DELETE_LINE_H_

#include "webkit/javascript.h"

namespace tools {

class JSDeleteLine : public  JavaScript {
 public:
  JSDeleteLine(long long id) : id_(id) {}
  virtual std::string execute();

 private:
  const long long id_;
};

} //namespace tools

#endif //TOOLS_WEBKIG_JS_DELETE_LINE_H_
