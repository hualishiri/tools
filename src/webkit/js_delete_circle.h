#ifndef TOOLS_OPERA_WEBKIT_JS_DELETE_CIRCLE_H_
#define TOOLS_OPERA_WEBKIT_JS_DELETE_CIRCLE_H_

#include "webkit/javascript.h"

namespace tools {

class JSDeleteCircle : public JavaScript{
public:
  JSDeleteCircle(long long id) : id_(id){}
  virtual std::string execute();
private:
  long long id_;
};

} //namespace tools

#endif //TOOLS_OPERA_WEBKIT_JS_DELETE_CIRCLE_H_
