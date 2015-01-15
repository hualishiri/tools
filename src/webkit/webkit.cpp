#include "webkit.h"

#include <sstream>
#include <cassert>

namespace tools{

Webkit* Webkit::webkit_ = NULL;
void Webkit::execute(JavaScript& js){
  assert(page_ != NULL);
  page_(js.execute().c_str());
}

Webkit* Webkit::Instance(){
  if(!webkit_) webkit_ = new Webkit();
  return webkit_;
}

std::string JSCreateObject::execute(){
 sstream_ << state_->id << ","
          << state_->x << ","
          << state_->y << ","
          << state_->acc << ","
          << state_->speed << ","
          << state_->angle;
 std::string js;
 js.append("createObject(");
 js.append(sstream_.str());
 js.append(");");
 sstream_.clear();
 return js;
}

std::string JSUpdateObject::execute(){
 sstream_ << state_->id << ","
          << state_->x << ","
          << state_->y << ","
          << state_->acc << ","
          << state_->speed << ","
          << state_->angle;
 std::string js;
 js.append("updateObject(");
 js.append(sstream_.str());
 js.append(");");
 sstream_.clear();
  return js;
}

std::string JSDeleteObject::execute(){
 sstream_ << id_;
 std::string js;
 js.append("deleteObject(");
 js.append(sstream_.str());
 js.append(");");
 sstream_.clear();
  return js;
}

std::string JSClearObject::execute(){
 std::string js;
    js = "clearObject();";
  return js;
}

std::string JSCreateRadar::execute(){
  sstream_ << radar_->id << ","
           << radar_->type << ","
           << radar_->center_x << ","
           << radar_->center_y << ","
           << radar_->radius;
 std::string js;
  js.append("createRadar(");
  js.append(sstream_.str());
  js.append(");");
  sstream_.clear();
  return js;
}

std::string JSUpdateRadar::execute(){
  sstream_ << radar_->id << ","
           << radar_->type << ","
           << radar_->center_x << ","
           << radar_->center_y << ","
           << radar_->radius;
 std::string js;
  js.append("updateRadar(");
  js.append(sstream_.str());
  js.append(");");
  sstream_.clear();
  return js;
}

std::string JSDeleteRadar::execute(){
 sstream_ << id_;
 std::string js;
 js.append("deleteRadar(");
 js.append(sstream_.str());
 js.append(");");
 sstream_.clear();
  return js;
}

std::string JSClearRadar::execute(){
 std::string js;
  js = "clearRadar();";
  return js;
}

std::string JSCreateRadarState::execute(){
  sstream_ << radar_id_ << ","
           << object_id_;
 std::string js;
  js.append("createRadarState(");
  js.append(sstream_.str());
  js.append(");");
  sstream_.clear();
  return js;
}

std::string JSUpdateRadarState::execute(){
  sstream_ << radar_id_ << ","
           << object_id_;
 std::string js;
  js.append("updateRadarState(");
  js.append(sstream_.str());
  js.append(");");
  sstream_.clear();
  return js;
}

std::string JSDeleteRadarState::execute(){
  sstream_ << radar_id_ << ","
           << object_id_;
 std::string js;
  js.append("deleteRadarState(");
  js.append(sstream_.str());
  js.append(");");
  sstream_.clear();
  return js;
}

std::string JSClearRadarState::execute(){
  sstream_ << radar_id_;
 std::string js;
  js.append("clearRadarState(");
  js.append(sstream_.str());
  js.append(");");
  sstream_.clear();
  return js;
}

std::string JSCreateLine::execute(){
  sstream_ << line_->id << ","
    << line_->start_x << ","
    << line_->start_y << ","
    << line_->end_x << ","
    << line_->end_y;
 std::string js;
  js.append("createLine(");
  js.append(sstream_.str());
  js.append(");");
  sstream_.clear();
  return js;
}

std::string JSUpdateLine::execute(){
  sstream_ << line_->id << ","
    << line_->start_x << ","
    << line_->start_y << ","
    << line_->end_x << ","
    << line_->end_y;
 std::string js;
  js.append("updateLine(");
  js.append(sstream_.str());
  js.append(");");
  sstream_.clear();
  return js;
}

std::string JSDeleteLine::execute(){
 sstream_ << id_;
 std::string js;
 js.append("deleteLine(");
 js.append(sstream_.str());
 js.append(");");
 sstream_.clear();
  return js;
}

std::string JSClearLine::execute(){
 std::string js;
  js = "clearLine();";
  return js;
}

std::string JSCreateCircle::execute(){
  sstream_ << circle_->id << ","
    << circle_->start_x << ","
    << circle_->start_y << ","
    << circle_->radius_x<< ","
    << circle_->radius_y<< ","
    << circle_->angle;
 std::string js;
  js.append("createCircle(");
  js.append(sstream_.str());
  js.append(");");
  sstream_.clear();
  return js;
}

std::string JSUpdateCircle::execute(){
  sstream_ << circle_->id << ","
    << circle_->start_x << ","
    << circle_->start_y << ","
    << circle_->radius_x<< ","
    << circle_->radius_y<< ","
    << circle_->angle;
 std::string js;
  js.append("updateCircle(");
  js.append(sstream_.str());
  js.append(");");
  sstream_.clear();
  return js;
}

std::string JSDeleteCircle::execute(){
 sstream_ << id_;
 std::string js;
 js.append("deleteCircle(");
 js.append(sstream_.str());
 js.append(");");
 sstream_.clear();
  return js;
}

std::string JSClearCircle::execute(){
 std::string js;
  js = "clearCircle();";
  return js;
}

std::string JSCreateEclipse::execute(){
  sstream_ << eclipse_->id << ","
    << eclipse_->start_x << ","
    << eclipse_->start_y << ","
    << eclipse_->radius_x<< ","
    << eclipse_->radius_y<< ","
    << eclipse_->end_x<< ","
    << eclipse_->end_y<< ","
    << eclipse_->angle;
 std::string js;
  js.append("createEclipse(");
  js.append(sstream_.str());
  js.append(");");
  sstream_.clear();
  return js;
}

std::string JSUpdateEclipse::execute(){
  sstream_ << eclipse_->id << ","
    << eclipse_->start_x << ","
    << eclipse_->start_y << ","
    << eclipse_->radius_x<< ","
    << eclipse_->radius_y<< ","
    << eclipse_->end_x<< ","
    << eclipse_->end_y<< ","
    << eclipse_->angle;
 std::string js;
  js.append("updateEclipse(");
  js.append(sstream_.str());
  js.append(");");
  sstream_.clear();
  return js;
}

std::string JSDeleteEclipse::execute(){
 sstream_ << id_;
 std::string js;
 js.append("deleteEclipse(");
 js.append(sstream_.str());
 js.append(");");
 sstream_.clear();
  return js;
}

std::string JSClearEclipse::execute(){
 std::string js;
  js = "clearEclipse();";
  return js;
}

std::string JSSetZoom::execute(){
  assert(zoom_ > 0 && zoom_ < 24);
  sstream_ << zoom_;
  std::string js;
  js.append("setZoom(");
  js.append(sstream_.str());
  js.append(");");
  sstream_.clear();
  return js;
}

std::string JSSetCenter::execute(){
  assert(longitude_ > -180.0 && longitude_ < 180.0);
  assert(latitude_ > -90.0 && latitude_ < 90.0);
  sstream_ << longitude_ << ","
    << latitude_;
  std::string js;
  js.append("setCenter(");
  js.append(sstream_.str());
  js.append(");");
  sstream_.clear();
  return js;
}

} //namespace tools
