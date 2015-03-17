#ifndef TOOLS_WEBKIG_JS_DELETE_OBJECT_H_
#define TOOLS_WEBKIG_JS_DELETE_OBJECT_H_

#include "webkit/javascript.h"

namespace tools {

class JSDeleteObject : public  JavaScript {
 public:
  JSDeleteObject(long long id)
    : id_(id) {
  }
  virtual std::string execute();

private:
    long long id_;
};

} //namespace tools

#endif //TOOLS_WEBKIG_JS_DELETE_OBJECT_H_
