#include "webkit/js_delete_line.h"

namespace tools {

std::string JSDeleteLine::execute(){
 sstream_ << id_;
 std::string js;
 js.append("deleteLine(");
 js.append(sstream_.str());
 js.append(");");
 sstream_.clear();
  return js;
}

}
