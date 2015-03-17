#ifndef TOOLS_WEBKIG_JS_UPDATE_LINE_H_
#define TOOLS_WEBKIG_JS_UPDATE_LINE_H_

#include "webkit/javascript.h"

namespace tools {

struct JSLine;

class JSUpdateLine : public  JavaScript {
 public:
  JSUpdateLine(const JSLine& line)
    : line_(line) {
  }
  virtual std::string execute();

 private:
  const JSLine& line_;
};

} //namespace tools

#endif //TOOLS_WEBKIG_JS_UPDATE_LINE_H_
