#include "webkit/js_update_object.h"

#include "util/testharness.h"

#include "webkit/js_create_object.h"

namespace tools {
  
class JSUPDATEOBJECT {};

TEST(JSUPDATEOBJECT, Execute) {
  std::string temp;
  std::stringstream strstream;
  JSObjectState object_state = {12, 12.34, 15,56};
  temp = JSUpdateObject(object_state).execute();
  strstream << "updateObject("
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
