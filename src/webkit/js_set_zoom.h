#ifndef TOOLS_WEBKIT_JS_SET_ZOOM_H_
#define TOOLS_WEBKIT_JS_SET_ZOOM_H_

#include "webkit/javascript.h"

namespace tools {

class JSSetZoom : public JavaScript{
public:
  JSSetZoom(int zoom):zoom_(zoom){}
  virtual std::string execute();
private:
  int zoom_;
};

} //namespace tools

#endif //TOOLS_WEBKIT_JS_SET_ZOOM_H_
