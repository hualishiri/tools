#include "webkit/webkit.h"

#include <assert.h>

namespace tools {

Webkit* Webkit::Instance() {
  if (!webkit_) webkit_ = new Webkit();
  return webkit_;
}

Webkit& Webkit::execute(JavaScript& js) {
  assert(page_ != NULL);
  page_(js.execute().c_str());
  return *this;
}

Webkit* Webkit::webkit_ = NULL;

} //namespace tools
