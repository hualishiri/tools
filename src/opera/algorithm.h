#ifndef TOOLS_OPERA_ALGORITHM_
#define TOOLS_OPERA_ALGORITHM_

namespace tools {

class Algorithm {
public:
  virtual void Handle(void* input, void* output) = 0;
};

} //namespace tools

#endif //TOOLS_OPERA_ALGORITHM_
