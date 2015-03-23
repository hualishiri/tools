#ifndef TOOLS_OPERA_WEBKIT_JS_CREATE_CIRCLE_H_
#define TOOLS_OPERA_WEBKIT_JS_CREATE_CIRCLE_H_

#include "webkit/javascript.h"

namespace tools {

struct JSCircle{
  long long id;
  double start_x;
  double start_y;
  double radius_x;
  double radius_y;
  double angle;
};

class JSCreateCircle : public JavaScript {
 public:
  JSCreateCircle(const JSCircle& circle) : circle_(circle) {}
  virtual std::string execute();

 private:
  const JSCircle& circle_;
};

} //namespace tools

#endif //TOOLS_OPERA_WEBKIT_JS_CREATE_CIRCLE_H_
