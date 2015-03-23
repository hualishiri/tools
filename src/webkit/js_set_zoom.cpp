#include "webkit/js_set_zoom.h"

#include <assert.h>

namespace tools {

std::string JSSetZoom::execute(){
  assert(zoom_ > 0 && zoom_ < 24);
  sstream_ << zoom_;
  std::string js;
  js.append("setZoom(");
  js.append(sstream_.str());
  js.append(");");
  sstream_.clear();
  return js;
}

} //namespace tools
