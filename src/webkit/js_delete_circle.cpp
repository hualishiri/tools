#include "webkit/js_delete_circle.h"

namespace tools {

std::string JSDeleteCircle::execute(){
 sstream_ << id_;
 std::string js;
 js.append("deleteCircle(");
 js.append(sstream_.str());
 js.append(");");
 sstream_.clear();
  return js;
}

} //namespace tools
