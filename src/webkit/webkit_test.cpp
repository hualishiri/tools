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

    TestSetZoom();
    TestSetCenter();
  }
private:
  void TestCreateObject(){
    std::string temp;
    std::stringstream strstream;
    ObjectState object_state = {12, 12.34, 15,56, 134.56, 23.12};
    temp = JSCreateObject(&object_state).execute();
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
    temp = JSUpdateObject(&object_state).execute();
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
    temp = JSDeleteObject(id).execute();
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
    mytemp = JSClearObject().execute();
    assert(strcmp(temp.c_str(), mytemp.c_str())== 0);
  }

  void TestCreateRadar(){
    std::string temp;
    std::stringstream strstream;
    JSRadar radar_state = { 1111, 0, 134.3241, 98.134, 431.12 };
    temp = JSCreateRadar(&radar_state).execute();
    strstream << "createRadar("
      << radar_state.id << ","
      << radar_state.type << ","
      << radar_state.center_x << ","
      << radar_state.center_y << ","
      << radar_state.radius;
    strstream << ");";
    strstream.flush();
    std::string mytemp = strstream.str();
    assert(strcmp(temp.c_str(), strstream.str().c_str()) == 0);

  }
  void TestUpdateRadar(){
    std::string temp;
    std::stringstream strstream;
    JSRadar radar_state = { 1111, 0,  134.3241, 30.0, 211.41 };
    temp = JSUpdateRadar(&radar_state).execute();
    strstream << "updateRadar("
      << radar_state.id << ","
      << radar_state.type << ","
      << radar_state.center_x << ","
      << radar_state.center_y << ","
      << radar_state.radius;
    strstream << ");";
    strstream.flush();
    std::string mytemp = strstream.str();
    assert(strcmp(temp.c_str(), strstream.str().c_str()) == 0);
  }
  void TestDeleteRadar(){
    std::string temp;
    std::stringstream strstream;
    unsigned long long id = 342189;
    temp = JSDeleteRadar(id).execute();
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
    mytemp = JSClearRadar().execute();
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
    temp = JSCreateRadarState(radar_id, object_id).execute();
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
    temp = JSUpdateRadarState(radar_id, object_id).execute();
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
    temp = JSDeleteRadarState(radar_id, object_id).execute();
    assert(strcmp(temp.c_str(), strstream.str().c_str()) == 0);
  }

  void TestClearRadarState(){
    std::string temp;
    std::stringstream strstream;
    unsigned long long radar_id = 4316432;
    strstream << "clearRadarState("
      << radar_id;
    strstream << ");";
    temp = JSClearRadarState(radar_id).execute();
    assert(strcmp(temp.c_str(), strstream.str().c_str()) == 0);
  }

  void TestCreateLine(){
    std::string temp;
    std::stringstream strstream;
    JSLine line = {342412, 123.4134, 73.132, 19.1411, 32.1341};
    strstream << "createLine("
      << line.id << ","
      << line.start_x << ","
      << line.start_y << ","
      << line.end_x << ","
      << line.end_y
      << ");";
    temp = JSCreateLine(&line).execute();
    assert(0 == strcmp(temp.c_str(), strstream.str().c_str()));
  }
  void TestUpdateLine(){
    std::string temp;
    std::stringstream strstream;
    JSLine line = {342412, 123.4134, 73.132, 19.1411, 32.1341};
    strstream << "updateLine("
      << line.id << ","
      << line.start_x << ","
      << line.start_y << ","
      << line.end_x << ","
      << line.end_y
      << ");";
    temp = JSUpdateLine(&line).execute();
    assert(0 == strcmp(temp.c_str(), strstream.str().c_str()));
  }
  void TestDeleteLine(){
    std::string temp;
    std::stringstream strstream;
    unsigned long long id = 141421;
    strstream << "deleteLine("
      << id
      << ");";
    temp = JSDeleteLine(id).execute();
    assert(0 == strcmp(temp.c_str(), strstream.str().c_str()));
  }
  void TestClearLine(){
    std::string temp;
    std::string temp_std = "clearLine();";
    temp = JSClearLine().execute();
    assert(0 == strcmp(temp.c_str(), temp_std.c_str()));
  }

  void TestCreateCircle(){
    std::string temp;
    std::stringstream strstream;
    JSCircle circle = {431289, 23.1341, 18.12431, 98.12421, 32.1341, 3.14};
    temp = JSCreateCircle(&circle).execute();
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
    JSCircle circle = {431289, 23.1341, 18.12431, 98.12421, 32.1341, 3.14};
    temp = JSUpdateCircle(&circle).execute();
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
    temp = JSDeleteCircle(id).execute();
    assert(0 == strcmp(temp.c_str(), strstream.str().c_str()));
  }
  void TestClearCircle(){
    std::string temp;
    std::string temp_std = "clearCircle();";
    temp = JSClearCircle().execute();
    assert(0 == strcmp(temp.c_str(), temp_std.c_str()));
  }

  void TestCreateEclipse(){
    std::string temp;
    std::stringstream strstream;
    Eclipse eclipse = {431289, 23.1341, 18.12431, 
      98.12421, 32.1341, 
      41.12432, 12.4321,
      3.14};
    temp = JSCreateEclipse(&eclipse).execute();
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
    temp =JSUpdateEclipse(&eclipse).execute();
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
    temp = JSDeleteEclipse(id).execute();
    assert(0 == strcmp(temp.c_str(), strstream.str().c_str()));
  }

  void TestClearEclipse(){
    std::string temp;
    std::string temp_std = "clearEclipse();";
    temp = JSClearEclipse().execute();
    assert(0 == strcmp(temp.c_str(), temp_std.c_str()));
  }

  void TestSetZoom(){
    std::string temp;
    std::stringstream strstream;
    unsigned long long id = 10;
    strstream << "setZoom("
      << id
      << ");";
    temp = JSSetZoom(id).execute();
    assert(0 == strcmp(temp.c_str(), strstream.str().c_str()));
  }

  void TestSetCenter(){
    std::string temp;
    std::stringstream strstream;
    double longitude = 170.4312;
    double latitude = 73.34121;
    strstream << "setCenter("
      << longitude << ","
      << latitude << ");";
    temp = JSSetCenter(longitude, latitude).execute();
    assert(0 == strcmp(temp.c_str(), strstream.str().c_str()));
  }
};

} //namespace test
} //namespace tools

int main(){
  tools::test::Test().RunAllTest();
  return 0;
}
