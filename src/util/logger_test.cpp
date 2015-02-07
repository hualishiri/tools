#define LOGDEBUG

#include "util/logger.h"

#include "util/testharness.h"

namespace tools {

class Empty {};

TEST(Empty, Init) {
  LogInfo("%s", "This is a test!");
  LogWarning("%s", "This is a Warning");
  LogError("%s", "This is a Error");
  LogCritical("%s", "This is a Critical");
  LogDebug("%s", "This is a Debug");
}

} //namespace tools

int main(int argc, char** argv) {
  return tools::test::RunAllTests();
}
