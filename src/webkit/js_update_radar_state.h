#ifndef TOOLS_OPERA_WEBKIT_JS_UPDATE_RADAR_STATE_H_
#define TOOLS_OPERA_WEBKIT_JS_UPDATE_RADAR_STATE_H_

#include "webkit/javascript.h"

namespace tools {

class JSUpdateRadarState : public JavaScript {
public:
    JSUpdateRadarState(long long radar_id,
                       long long object_id)
        :radar_id_(radar_id), object_id_(object_id){}
    virtual std::string execute();
private:
    long long radar_id_;
    long long object_id_;
};

} //namespace tools

#endif //TOOLS_OPERA_WEBKIT_JS_UPDATE_RADAR_STATE_H_
