#include "webkit/js_create_object.h"

#include "util/testharness.h"

namespace tools {

class JSCREATEOBJECT {};

TEST(JSCREATEOBJECT, Execute) {
  std::string temp;
  std::stringstream strstream;
  JSObjectState object_state = {12, 12.34, 15,56, 134.56, 23.12};
  temp = JSCreateObject(object_state).execute();
  strstream << "createObject("
      << object_state.id << ","
      << object_state.x << ","
      << object_state.y << ","
      << object_state.acc << ","
      << object_state.speed<< ","
      << object_state.angle;
  strstream << ");";
  strstream.flush();
  std::string mytemp = strstream.str();
  ASSERT_EQ(strcmp(temp.c_str(), strstream.str().c_str()), 0);
}

} //namespace tools

int main(int argc, char** argv) {
  return tools::test::RunAllTests();
}
