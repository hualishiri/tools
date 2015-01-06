#include "webkit.h"
//#include <QWebFrame>

#include <sstream>

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
