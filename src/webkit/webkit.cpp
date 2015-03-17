#include "webkit/webkit.h"

#include <assert.h>

namespace tools {

Webkit* Webkit::Instance() {
  if (!webkit_) webkit_ = new Webkit();
  return webkit_;
}

Webkit& Webkit::execute(JavaScript& js) {
  assert(page_ != NULL);
  page_(js.execute().c_str());
  return *this;
}

Webkit* Webkit::webkit_ = NULL;

/*

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
           << std::setprecision(precision) << radar_->center_x << ","
           << std::setprecision(precision) << radar_->center_y << ","
           << std::setprecision(precision) << radar_->radius;
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
           << std::setprecision(precision) << radar_->center_x << ","
           << std::setprecision(precision) << radar_->center_y << ","
           << std::setprecision(precision) << radar_->radius;
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
    <<  std::setprecision(precision) << line_->start_x << ","
    <<  std::setprecision(precision) << line_->start_y << ","
    <<  std::setprecision(precision) << line_->end_x << ","
    <<  std::setprecision(precision) << line_->end_y;
 std::string js;
  js.append("createLine(");
  js.append(sstream_.str());
  js.append(");");
  sstream_.clear();
  return js;
}

std::string JSUpdateLine::execute(){
  sstream_ << line_->id << ","
    << std::setprecision(precision) << line_->start_x << ","
    << std::setprecision(precision) << line_->start_y << ","
    << std::setprecision(precision) << line_->end_x << ","
    << std::setprecision(precision) << line_->end_y;
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
    << std::setprecision(precision) << circle_->start_x << ","
    << std::setprecision(precision) << circle_->start_y << ","
    << std::setprecision(precision) << circle_->radius_x<< ","
    << std::setprecision(precision) << circle_->radius_y<< ","
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
    << std::setprecision(precision) << circle_->start_x << ","
    << std::setprecision(precision) << circle_->start_y << ","
    << std::setprecision(precision) << circle_->radius_x<< ","
    << std::setprecision(precision) << circle_->radius_y<< ","
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
    << std::setprecision(precision) << eclipse_->start_x << ","
    << std::setprecision(precision) << eclipse_->start_y << ","
    << std::setprecision(precision) << eclipse_->radius_x<< ","
    << std::setprecision(precision) << eclipse_->radius_y<< ","
    << std::setprecision(precision) << eclipse_->end_x<< ","
    << std::setprecision(precision) << eclipse_->end_y<< ","
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
    << std::setprecision(precision) << eclipse_->start_x << ","
    << std::setprecision(precision) << eclipse_->start_y << ","
    << std::setprecision(precision) << eclipse_->radius_x<< ","
    << std::setprecision(precision) << eclipse_->radius_y<< ","
    << std::setprecision(precision) << eclipse_->end_x<< ","
    << std::setprecision(precision) << eclipse_->end_y<< ","
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
  sstream_ << std::setprecision(precision) << longitude_ << ","
    << std::setprecision(precision) << latitude_;
  std::string js;
  js.append("setCenter(");
  js.append(sstream_.str());
  js.append(");");
  sstream_.clear();
  return js;
}
*/
} //namespace tools
