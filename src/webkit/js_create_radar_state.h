#include "webkit/javascript.h"

namespace tools {

class JSCreateRadarState : public JavaScript{
public:
  JSCreateRadarState(long long radar_id,
    long long object_id)
    :radar_id_(radar_id), object_id_(object_id){}
  virtual std::string execute();
private:
    long long radar_id_;
    long long object_id_;
};

} //namespace tools
