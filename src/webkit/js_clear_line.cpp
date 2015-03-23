#include "webkit/js_clear_line.h"

namespace tools {

std::string JSClearLine::execute(){
 std::string js;
  js = "clearLine();";
  return js;
}

} //namespace tools
