#ifndef TOOLS_WEBKIT_JAVASCRIPT_H_
#define TOOLS_WEBKIT_JAVASCRIPT_H_

#include <cstring>
#include <sstream>

namespace tools {

class JavaScript {
 public:
  virtual ~JavaScript() {}

  virtual std::string execute() = 0;

 protected:
  enum { kPrecision = 10 };

  std::stringstream sstream_;
};

} //namespace tools

#endif //TOOLS_WEBKIT_JAVASCRIPT_H_
