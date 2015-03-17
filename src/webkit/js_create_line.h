#ifndef TOOLS_WEBKIG_JS_CREATE_LINE_H_
#define TOOLS_WEBKIG_JS_CREATE_LINE_H_

#include "webkit/javascript.h"

namespace tools {

struct JSLine {
  long long id;
  double start_x;
  double start_y;
  double end_x;
  double end_y;
};

class JSCreateLine : public  JavaScript {
 public:
  JSCreateLine(const JSLine& line)
    : line_(line) {
  }
  virtual std::string execute();

 private:
  const JSLine& line_;
};

} //namespace tools

#endif //TOOLS_WEBKIG_JS_CREATE_LINE_H_
