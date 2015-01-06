#include "webkit.h"

#include <sstream>

namespace tools{

void JSCreateObject::execute(std::string& js){
 sstream_ << state_->id << ","
          << state_->x << ","
          << state_->y << ","
          << state_->acc << ","
          << state_->speed << ","
          << state_->angle;
 js.append("createObject(");
 js.append(sstream_.str());
 js.append(");");
 sstream_.clear();
}

void JSUpdateObject::execute(std::string& js){
 sstream_ << state_->id << ","
          << state_->x << ","
          << state_->y << ","
          << state_->acc << ","
          << state_->speed << ","
          << state_->angle;
 js.append("updateObject(");
 js.append(sstream_.str());
 js.append(");");
 sstream_.clear();
}

void JSDeleteObject::execute(std::string& js){
 sstream_ << id_;
 js.append("deleteObject(");
 js.append(sstream_.str());
 js.append(");");
 sstream_.clear();
}

void JSClearObject::execute(std::string& js){
    js = "clearObject();";
}

void JSCreateRadar::execute(std::string &js){
  sstream_ << radar_->id << ","
           << radar_->x << ","
           << radar_->y;
  js.append("createRadar(");
  js.append(sstream_.str());
  js.append(");");
  sstream_.clear();
}

void JSUpdateRadar::execute(std::string &js){
  sstream_ << radar_->id << ","
           << radar_->x << ","
           << radar_->y;
  js.append("updateRadar(");
  js.append(sstream_.str());
  js.append(");");
  sstream_.clear();
}

void JSDeleteRadar::execute(std::string &js){
 sstream_ << id_;
 js.append("deleteRadar(");
 js.append(sstream_.str());
 js.append(");");
 sstream_.clear();
}

void JSClearRadar::execute(std::string &js){
  js = "clearRadar();";
}

void JSCreateRadarState::execute(std::string &js){
  sstream_ << radar_id_ << ","
           << object_id_;
  js.append("createRadarState(");
  js.append(sstream_.str());
  js.append(");");
  sstream_.clear();
}

void JSUpdateRadarState::execute(std::string &js){
  sstream_ << radar_id_ << ","
           << object_id_;
  js.append("updateRadarState(");
  js.append(sstream_.str());
  js.append(");");
  sstream_.clear();
}

void JSDeleteRadarState::execute(std::string &js){
  sstream_ << radar_id_ << ","
           << object_id_;
  js.append("deleteRadarState(");
  js.append(sstream_.str());
  js.append(");");
  sstream_.clear();
}

void JSClearRadarState::execute(std::string &js){
  sstream_ << radar_id_;
  js.append("clearRadarState(");
  js.append(sstream_.str());
  js.append(");");
  sstream_.clear();
}

void JSCreateLine::execute(std::string &js){
  sstream_ << line_->id << ","
    << line_->start_x << ","
    << line_->start_y << ","
    << line_->end_x << ","
    << line_->end_y;
  js.append("createLine(");
  js.append(sstream_.str());
  js.append(");");
  sstream_.clear();
}

void JSUpdateLine::execute(std::string &js){
  sstream_ << line_->id << ","
    << line_->start_x << ","
    << line_->start_y << ","
    << line_->end_x << ","
    << line_->end_y;
  js.append("updateLine(");
  js.append(sstream_.str());
  js.append(");");
  sstream_.clear();
}

void JSDeleteLine::execute(std::string &js){
 sstream_ << id_;
 js.append("deleteLine(");
 js.append(sstream_.str());
 js.append(");");
 sstream_.clear();
}

void JSClearLine::execute(std::string &js){
  js = "clearLine();";
}

void JSCreateCircle::execute(std::string &js){
  sstream_ << circle_->id << ","
    << circle_->start_x << ","
    << circle_->start_y << ","
    << circle_->radius_x<< ","
    << circle_->radius_y<< ","
    << circle_->angle;
  js.append("createCircle(");
  js.append(sstream_.str());
  js.append(");");
  sstream_.clear();
}

void JSUpdateCircle::execute(std::string &js){
  sstream_ << circle_->id << ","
    << circle_->start_x << ","
    << circle_->start_y << ","
    << circle_->radius_x<< ","
    << circle_->radius_y<< ","
    << circle_->angle;
  js.append("updateCircle(");
  js.append(sstream_.str());
  js.append(");");
  sstream_.clear();
}

void JSDeleteCircle::execute(std::string &js){
 sstream_ << id_;
 js.append("deleteCircle(");
 js.append(sstream_.str());
 js.append(");");
 sstream_.clear();
}

void JSClearCircle::execute(std::string &js){
  js = "clearCircle();";
}

void JSCreateEclipse::execute(std::string &js){
  sstream_ << eclipse_->id << ","
    << eclipse_->start_x << ","
    << eclipse_->start_y << ","
    << eclipse_->radius_x<< ","
    << eclipse_->radius_y<< ","
    << eclipse_->end_x<< ","
    << eclipse_->end_y<< ","
    << eclipse_->angle;
  js.append("createEclipse(");
  js.append(sstream_.str());
  js.append(");");
  sstream_.clear();
}

void JSUpdateEclipse::execute(std::string &js){
  sstream_ << eclipse_->id << ","
    << eclipse_->start_x << ","
    << eclipse_->start_y << ","
    << eclipse_->radius_x<< ","
    << eclipse_->radius_y<< ","
    << eclipse_->end_x<< ","
    << eclipse_->end_y<< ","
    << eclipse_->angle;
  js.append("updateEclipse(");
  js.append(sstream_.str());
  js.append(");");
  sstream_.clear();
}

void JSDeleteEclipse::execute(std::string &js){
 sstream_ << id_;
 js.append("deleteEclipse(");
 js.append(sstream_.str());
 js.append(");");
 sstream_.clear();
}

void JSClearEclipse::execute(std::string &js){
  js = "clearEclipse();";
}

} //namespace tools
