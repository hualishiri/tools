#ifndef TOOLS_WEBKIG_JS_DELETE_RADAR_H_
#define TOOLS_WEBKIG_JS_DELETE_RADAR_H_

#include "webkit/javascript.h"

namespace tools {

struct JSRadar;

class JSDeleteRadar : public  JavaScript {
 public:
  JSDeleteRadar(long long id) : id_(id) {}
  virtual std::string execute();

 private:
  long long id_;
};

} //namespace tools

#endif //TOOLS_WEBKIG_JS_DELETE_RADAR_H_
