#ifndef TOOLS_WEBKIT_JS_SET_CENTER_H_
#define TOOLS_WEBKIT_JS_SET_CENTER_H_

#include "webkit/javascript.h"

namespace tools {

class JSSetCenter : public JavaScript{
public:
  JSSetCenter(double longitude, double latitude)
    :longitude_(longitude), latitude_(latitude){}
  virtual std::string execute();
private:
  double longitude_;
  double latitude_;
};

} //namespace tools

#endif //TOOLS_WEBKIT_JS_SET_CENTER_H_
