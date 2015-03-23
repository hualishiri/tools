#include "webkit/js_delete_object.h"

namespace tools {

std::string JSDeleteObject::execute(){
 sstream_ << id_;
 std::string js;
 js.append("deleteObject(");
 js.append(sstream_.str());
 js.append(");");
 sstream_.clear();
  return js;
}

} //namespace tools
