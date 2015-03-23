#ifndef TOOLS_WEBKIT_WEBKIT_H_ 
#define TOOLS_WEBKIT_WEBKIT_H_ 

#include "webkit/javascript.h"

namespace tools {

class Webkit {
 public:
  static Webkit* Instance();

  Webkit& execute(JavaScript& js);
  inline void set_page(void(*page)(const char*)) { page_ = page; }
  
 private:
  Webkit(){}
  Webkit(const Webkit&);
  Webkit& operator=(const Webkit&);

  static Webkit* webkit_;
  void (*page_)(const char*);
};

} //namespace tools

#endif // TOOLS_WEBKIT_WEBKIT_H
