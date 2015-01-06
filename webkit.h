#ifndef WEBKIT_H
#define WEBKIT_H

#include <cstring>
#include <sstream>

namespace tools{

class JavaScript{
public:
    virtual void execute(std::string& js) = 0;
protected:
    std::stringstream sstream_;
};

struct ObjectState{
  unsigned long long id;
  double x;
  double y;
  double acc;
  double speed;
  double angle;
};

class JSCreateObject : JavaScript{
public:
    JSCreateObject(ObjectState * state)
        :state_(state){}
    virtual void execute(std::string& js);
private:
    ObjectState* state_;
};

class JSUpdateObject: JavaScript{
public:
    JSUpdateObject(ObjectState * state)
        :state_(state){}
    virtual void execute(std::string& js);
private:
    ObjectState* state_;
};

class JSDeleteObject: JavaScript{
public:
    JSDeleteObject(unsigned long long id)
        :id_(id){}
    virtual void execute(std::string& js);
private:
    unsigned long long id_;
};

class JSClearObject: JavaScript{
public:
    virtual void execute(std::string& js);
private:
};

struct Radar{
  unsigned long long id;
  double x;
  double y;
};

class JSCreateRadar:public JavaScript{
public:
    JSCreateRadar(Radar *radar):radar_(radar){}
    virtual void execute(std::string& js);
private:
    Radar* radar_;
};

class JSUpdateRadar:public JavaScript{
public:
    JSUpdateRadar(Radar *radar):radar_(radar){}
    virtual void execute(std::string& js);
private:
    Radar* radar_;
};

class JSDeleteRadar:public JavaScript{
public:
    JSDeleteRadar(unsigned long long id):id_(id){}
    virtual void execute(std::string& js);
private:
    unsigned long long id_;
};

class JSClearRadar:public JavaScript{
public:
    virtual void execute(std::string& js);
private:
};

class JSCreateRadarState : public JavaScript{
public:
  JSCreateRadarState(unsigned long long radar_id,
    unsigned long long object_id)
    :radar_id_(radar_id), object_id_(object_id){}
  virtual void execute(std::string& js);
private:
    unsigned long long radar_id_;
    unsigned long long object_id_;
};

class JSUpdateRadarState:public JavaScript{
public:
    JSUpdateRadarState(unsigned long long radar_id,
                       unsigned long long object_id)
        :radar_id_(radar_id), object_id_(object_id){}
    virtual void execute(std::string& js);
private:
    unsigned long long radar_id_;
    unsigned long long object_id_;
};

class JSDeleteRadarState:public JavaScript{
public:
    JSDeleteRadarState(unsigned long long radar_id,
                       unsigned long long object_id)
        :radar_id_(radar_id), object_id_(object_id){}
    virtual void execute(std::string& js);
private:
    unsigned long long radar_id_;
    unsigned long long object_id_;
};

class JSClearRadarState:public JavaScript{
public:
    JSClearRadarState(unsigned long long radar_id):radar_id_(radar_id){}
    virtual void execute(std::string& js);
private:
    unsigned long long radar_id_;
};

struct Line{
  unsigned long long id;
  double start_x;
  double start_y;
  double end_x;
  double end_y;
};

class JSCreateLine:public JavaScript{
public:
  JSCreateLine(Line* line) : line_ (line){}
  virtual void execute(std::string &js);
private:
  Line* line_;
};

class JSUpdateLine:public JavaScript{
public:
  JSUpdateLine(Line* line) : line_ (line){}
  virtual void execute(std::string &js);
private:
  Line* line_;
};

class JSDeleteLine : public JavaScript{
public:
  JSDeleteLine(unsigned long long id) : id_(id){}
  virtual void execute(std::string &js);
private:
  unsigned long long id_;
};

class JSClearLine : public JavaScript{
public:
  virtual void execute(std::string &js);
};

struct Circle{
  unsigned long long id;
  double start_x;
  double start_y;
  double radius_x;
  double radius_y;
  double angle;
};


class JSCreateCircle:public JavaScript{
public:
  JSCreateCircle(Circle* circle) : circle_(circle){}
  virtual void execute(std::string &js);
private:
  Circle* circle_;
};

class JSUpdateCircle:public JavaScript{
public:
  JSUpdateCircle(Circle* circle) : circle_(circle){}
  virtual void execute(std::string &js);
private:
  Circle* circle_;
};

class JSDeleteCircle : public JavaScript{
public:
  JSDeleteCircle(unsigned long long id) : id_(id){}
  virtual void execute(std::string &js);
private:
  unsigned long long id_;
};

class JSClearCircle : public JavaScript{
public:
  virtual void execute(std::string &js);
};

struct Eclipse{
  unsigned long long id;
  double start_x;
  double start_y;
  double radius_x;
  double radius_y;
  double end_x;
  double end_y;
  double angle;
};

class JSCreateEclipse:public JavaScript{
public:
  JSCreateEclipse(Eclipse* eclipse) : eclipse_(eclipse){}
  virtual void execute(std::string &js);
private:
  Eclipse* eclipse_;
};

class JSUpdateEclipse:public JavaScript{
public:
  JSUpdateEclipse(Eclipse* eclipse) : eclipse_(eclipse){}
  virtual void execute(std::string &js);
private:
  Eclipse* eclipse_;
};

class JSDeleteEclipse : public JavaScript{
public:
  JSDeleteEclipse(unsigned long long id) : id_(id){}
  virtual void execute(std::string &js);
private:
  unsigned long long id_;
};

class JSClearEclipse : public JavaScript{
public:
  virtual void execute(std::string &js);
};

} //namespace tools

#endif // WEBKIT_H
