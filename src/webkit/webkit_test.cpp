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

    TestCreateLine();
    TestUpdateLine();
    TestDeleteLine();
    TestClearLine();
  
    TestCreateEclipse();
    TestUpdateEclipse();
    TestDeleteEclipse();
    TestClearEclipse();
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

  void TestCreateLine(){
    std::string temp;
    std::stringstream strstream;
    Line line = {342412, 123.4134, 73.132, 19.1411, 32.1341};
    strstream << "createLine("
      << line.id << ","
      << line.start_x << ","
      << line.start_y << ","
      << line.end_x << ","
      << line.end_y
      << ");";
    JSCreateLine(&line).execute(temp);
    assert(0 == strcmp(temp.c_str(), strstream.str().c_str()));
  }
  void TestUpdateLine(){
    std::string temp;
    std::stringstream strstream;
    Line line = {342412, 123.4134, 73.132, 19.1411, 32.1341};
    strstream << "updateLine("
      << line.id << ","
      << line.start_x << ","
      << line.start_y << ","
      << line.end_x << ","
      << line.end_y
      << ");";
    JSUpdateLine(&line).execute(temp);
    assert(0 == strcmp(temp.c_str(), strstream.str().c_str()));
  }
  void TestDeleteLine(){
    std::string temp;
    std::stringstream strstream;
    unsigned long long id = 141421;
    strstream << "deleteLine("
      << id
      << ");";
    JSDeleteLine(id).execute(temp);
    assert(0 == strcmp(temp.c_str(), strstream.str().c_str()));
  }
  void TestClearLine(){
    std::string temp;
    std::string temp_std = "clearLine();";
    JSClearLine().execute(temp);
    assert(0 == strcmp(temp.c_str(), temp_std.c_str()));
  }

  void TestCreateCircle(){
    std::string temp;
    std::stringstream strstream;
    Circle circle = {431289, 23.1341, 18.12431, 98.12421, 32.1341, 3.14};
    JSCreateCircle(&circle).execute(temp);
    strstream << "createCircle(" 
      << circle.id << ","
      << circle.start_x << ","
      << circle.start_y << ","
      << circle.radius_x << ","
      << circle.radius_y << ","
      << circle.angle
      << ");";
    assert(0 == strcmp(temp.c_str(), strstream.str().c_str()));
  }
  void TestUpdateiCircle(){
    std::string temp;
    std::stringstream strstream;
    Circle circle = {431289, 23.1341, 18.12431, 98.12421, 32.1341, 3.14};
    JSUpdateCircle(&circle).execute(temp);
    strstream << "updateCircle(" 
      << circle.id << ","
      << circle.start_x << ","
      << circle.start_y << ","
      << circle.radius_x << ","
      << circle.radius_y << ","
      << circle.angle
      << ");";
    assert(0 == strcmp(temp.c_str(), strstream.str().c_str()));
  }
  void TestDeleteCircle(){
    std::string temp;
    std::stringstream strstream;
    unsigned long long id = 141421;
    strstream << "deleteCircle("
      << id
      << ");";
    JSDeleteCircle(id).execute(temp);
    assert(0 == strcmp(temp.c_str(), strstream.str().c_str()));
  }
  void TestClearCircle(){
    std::string temp;
    std::string temp_std = "clearCircle();";
    JSClearCircle().execute(temp);
    assert(0 == strcmp(temp.c_str(), temp_std.c_str()));
  }

  void TestCreateEclipse(){
    std::string temp;
    std::stringstream strstream;
    Eclipse eclipse = {431289, 23.1341, 18.12431, 
      98.12421, 32.1341, 
      41.12432, 12.4321,
      3.14};
    JSCreateEclipse(&eclipse).execute(temp);
    strstream << "createEclipse(" 
      << eclipse.id << ","
      << eclipse.start_x << ","
      << eclipse.start_y << ","
      << eclipse.radius_x << ","
      << eclipse.radius_y << ","
      << eclipse.end_x << ","
      << eclipse.end_y << ","
      << eclipse.angle
      << ");";
    assert(0 == strcmp(temp.c_str(), strstream.str().c_str()));
  }

  void TestUpdateEclipse(){
    std::string temp;
    std::stringstream strstream;
    Eclipse eclipse = {431289, 23.1341, 18.12431, 
      98.12421, 32.1341, 
      41.12432, 12.4321,
      3.14};
    JSUpdateEclipse(&eclipse).execute(temp);
    strstream << "updateEclipse(" 
      << eclipse.id << ","
      << eclipse.start_x << ","
      << eclipse.start_y << ","
      << eclipse.radius_x << ","
      << eclipse.radius_y << ","
      << eclipse.end_x << ","
      << eclipse.end_y << ","
      << eclipse.angle
      << ");";
    assert(0 == strcmp(temp.c_str(), strstream.str().c_str()));
  }

  void TestDeleteEclipse(){
    std::string temp;
    std::stringstream strstream;
    unsigned long long id = 141421;
    strstream << "deleteEclipse("
      << id
      << ");";
    JSDeleteEclipse(id).execute(temp);
    assert(0 == strcmp(temp.c_str(), strstream.str().c_str()));
  }

  void TestClearEclipse(){
    std::string temp;
    std::string temp_std = "clearEclipse();";
    JSClearEclipse().execute(temp);
    assert(0 == strcmp(temp.c_str(), temp_std.c_str()));
  }
};

} //namespace test
} //namespace tools

int main(){
  tools::test::Test().RunAllTest();
  return 0;
}
