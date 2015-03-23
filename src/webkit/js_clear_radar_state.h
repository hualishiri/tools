#ifndef TOOLS_OPERA_WEBKIT_JS_CLEAR_RADAR_STATE_H_
#define TOOLS_OPERA_WEBKIT_JS_CLEAR_RADAR_STATE_H_

#include "webkit/javascript.h"

namespace tools {

class JSClearRadarState:public JavaScript{
public:
    JSClearRadarState(long long radar_id):radar_id_(radar_id){}
    virtual std::string execute();
private:
    long long radar_id_;
};

} //namespace tools

#endif //TOOLS_OPERA_WEBKIT_JS_CLEAR_RADAR_STATE_H_
