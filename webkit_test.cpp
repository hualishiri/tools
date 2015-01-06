#include "webkit.h"

#include <cstring>
#include <sstream>
#include <cassert>

namespace tools{
namespace test{

class Test{
public:
  void RunAllTest(){
    TestCreateObject();
    TestUpdateObject();
    TestDeleteObject();
    TestClearObject();

    TestCreateRadar();
    TestUpdateRadar();
    TestDeleteRadar();
    TestClearRadar();
  
    TestCreateRadarState();
    TestUpdateRadarState();
    TestDeleteRadarState();
    TestClearRadarState();
  }
private:
  void TestCreateObject(){
    std::string temp;
    std::stringstream strstream;
    ObjectState object_state = {12, 12.34, 15,56, 134.56, 23.12};
    JSCreateObject(&object_state).execute(temp);
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
    assert(strcmp(temp.c_str(), strstream.str().c_str()) == 0);
  }

  void TestUpdateObject(){
    std::string temp;
    std::stringstream strstream;
    ObjectState object_state = {12, 12.34, 15,56};
    JSUpdateObject(&object_state).execute(temp);
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
    assert(strcmp(temp.c_str(), strstream.str().c_str()) == 0);
  }

  void TestDeleteObject(){
    std::string temp;
    std::stringstream strstream;
    unsigned long long id = 101010;
    JSDeleteObject(id).execute(temp);
    strstream << "deleteObject("
      << id;
    strstream << ");";
    strstream.flush();
    std::string mytemp = strstream.str();
    assert(strcmp(temp.c_str(), strstream.str().c_str()) == 0);
  }

  void TestClearObject(){
    std::string temp = "clearObject();";
    std::string mytemp;
    JSClearObject().execute(mytemp);
    assert(strcmp(temp.c_str(), mytemp.c_str())== 0);
  }

  void TestCreateRadar(){
    std::string temp;
    std::stringstream strstream;
    Radar radar_state = { 1111, 134.3241, 98.134 };
    JSCreateRadar(&radar_state).execute(temp);
    strstream << "createRadar("
      << radar_state.id << ","
      << radar_state.x << ","
      << radar_state.y;
    strstream << ");";
    strstream.flush();
    std::string mytemp = strstream.str();
    assert(strcmp(temp.c_str(), strstream.str().c_str()) == 0);

  }
  void TestUpdateRadar(){
    std::string temp;
    std::stringstream strstream;
    Radar radar_state = { 1111, 134.3241, 98.134 };
    JSUpdateRadar(&radar_state).execute(temp);
    strstream << "updateRadar("
      << radar_state.id << ","
      << radar_state.x << ","
      << radar_state.y;
    strstream << ");";
    strstream.flush();
    std::string mytemp = strstream.str();
    assert(strcmp(temp.c_str(), strstream.str().c_str()) == 0);
  }
  void TestDeleteRadar(){
    std::string temp;
    std::stringstream strstream;
    unsigned long long id = 342189;
    JSDeleteRadar(id).execute(temp);
    strstream << "deleteRadar("
      << id;
    strstream << ");";
    strstream.flush();
    std::string mytemp = strstream.str();
    assert(strcmp(temp.c_str(), strstream.str().c_str()) == 0);
  }
  void TestClearRadar(){
    std::string temp = "clearRadar();";
    std::string mytemp;
    JSClearRadar().execute(mytemp);
    assert(strcmp(temp.c_str(), mytemp.c_str()) == 0);
  }

  void TestCreateRadarState(){
    std::string temp;
    std::stringstream strstream;
    unsigned long long radar_id = 4316432;
    unsigned long long object_id = 16438184;
    strstream << "createRadarState("
      << radar_id << ","
      << object_id;
    strstream << ");";
    JSCreateRadarState(radar_id, object_id).execute(temp);
    std::string mytemp = strstream.str();
    assert(strcmp(temp.c_str(), strstream.str().c_str()) == 0);
  }

  void TestUpdateRadarState(){
    std::string temp;
    std::stringstream strstream;
    unsigned long long radar_id = 4316432;
    unsigned long long object_id = 16438184;
    strstream << "updateRadarState("
      << radar_id << ","
      << object_id;
    strstream << ");";
    JSUpdateRadarState(radar_id, object_id).execute(temp);
    assert(strcmp(temp.c_str(), strstream.str().c_str()) == 0);
  }

  void TestDeleteRadarState(){
    std::string temp;
    std::stringstream strstream;
    unsigned long long radar_id = 4316432;
    unsigned long long object_id = 16438184;
    strstream << "deleteRadarState("
      << radar_id << ","
      << object_id;
    strstream << ");";
    JSDeleteRadarState(radar_id, object_id).execute(temp);
    assert(strcmp(temp.c_str(), strstream.str().c_str()) == 0);
  }

  void TestClearRadarState(){
    std::string temp;
    std::stringstream strstream;
    unsigned long long radar_id = 4316432;
    strstream << "clearRadarState("
      << radar_id;
    strstream << ");";
    JSClearRadarState(radar_id).execute(temp);
    assert(strcmp(temp.c_str(), strstream.str().c_str()) == 0);
  }
};

} //namespace test
} //namespace tools

int main(){
  tools::test::Test().RunAllTest();
  return 0;
}
