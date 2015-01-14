#ifndef WEBKIT_H
#define WEBKIT_H

#include <cstring>
#include <sstream>

namespace tools{

class JavaScript{
public:
    virtual std::string execute() = 0;
protected:
    std::stringstream sstream_;
};

class Webkit{
public:
  void execute(JavaScript& js);
  inline void set_page(void(*page)(const char*)) { page_ = page; }
  static Webkit* Instance();
  
private:
  Webkit(){}
  Webkit(const Webkit&);
  Webkit& operator=(const Webkit&);

  void (*page_)(const char*);
  static Webkit* webkit_;
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
    virtual std::string execute();
private:
    ObjectState* state_;
};

class JSUpdateObject: JavaScript{
public:
    JSUpdateObject(ObjectState * state)
        :state_(state){}
    virtual std::string execute();
private:
    ObjectState* state_;
};

class JSDeleteObject: JavaScript{
public:
    JSDeleteObject(unsigned long long id)
        :id_(id){}
    virtual std::string execute();
private:
    unsigned long long id_;
};

class JSClearObject: JavaScript{
public:
    virtual std::string execute();
private:
};

struct JSRadar{
  long long id;
  int type;
  double center_x;
  double center_y;
  double radius;
};

class JSCreateRadar:public JavaScript{
public:
    JSCreateRadar(JSRadar *radar):radar_(radar){}
    virtual std::string execute();
private:
    JSRadar* radar_;
};

class JSUpdateRadar:public JavaScript{
public:
    JSUpdateRadar(JSRadar *radar):radar_(radar){}
    virtual std::string execute();
private:
    JSRadar* radar_;
};

class JSDeleteRadar:public JavaScript{
public:
    JSDeleteRadar(unsigned long long id):id_(id){}
    virtual std::string execute();
private:
    unsigned long long id_;
};

class JSClearRadar:public JavaScript{
public:
    virtual std::string execute();
private:
};

class JSCreateRadarState : public JavaScript{
public:
  JSCreateRadarState(unsigned long long radar_id,
    unsigned long long object_id)
    :radar_id_(radar_id), object_id_(object_id){}
  virtual std::string execute();
private:
    unsigned long long radar_id_;
    unsigned long long object_id_;
};

class JSUpdateRadarState:public JavaScript{
public:
    JSUpdateRadarState(unsigned long long radar_id,
                       unsigned long long object_id)
        :radar_id_(radar_id), object_id_(object_id){}
    virtual std::string execute();
private:
    unsigned long long radar_id_;
    unsigned long long object_id_;
};

class JSDeleteRadarState:public JavaScript{
public:
    JSDeleteRadarState(unsigned long long radar_id,
                       unsigned long long object_id)
        :radar_id_(radar_id), object_id_(object_id){}
    virtual std::string execute();
private:
    unsigned long long radar_id_;
    unsigned long long object_id_;
};

class JSClearRadarState:public JavaScript{
public:
    JSClearRadarState(unsigned long long radar_id):radar_id_(radar_id){}
    virtual std::string execute();
private:
    unsigned long long radar_id_;
};

struct JSLine{
  unsigned long long id;
  double start_x;
  double start_y;
  double end_x;
  double end_y;
};

class JSCreateLine:public JavaScript{
public:
  JSCreateLine(JSLine* line) : line_ (line){}
  virtual std::string execute();
private:
  JSLine* line_;
};

class JSUpdateLine:public JavaScript{
public:
  JSUpdateLine(JSLine* line) : line_ (line){}
  virtual std::string execute();
private:
  JSLine* line_;
};

class JSDeleteLine : public JavaScript{
public:
  JSDeleteLine(unsigned long long id) : id_(id){}
  virtual std::string execute();
private:
  unsigned long long id_;
};

class JSClearLine : public JavaScript{
public:
  virtual std::string execute();
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
  virtual std::string execute();
private:
  Circle* circle_;
};

class JSUpdateCircle:public JavaScript{
public:
  JSUpdateCircle(Circle* circle) : circle_(circle){}
  virtual std::string execute();
private:
  Circle* circle_;
};

class JSDeleteCircle : public JavaScript{
public:
  JSDeleteCircle(unsigned long long id) : id_(id){}
  virtual std::string execute();
private:
  unsigned long long id_;
};

class JSClearCircle : public JavaScript{
public:
  virtual std::string execute();
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
  virtual std::string execute();
private:
  Eclipse* eclipse_;
};

class JSUpdateEclipse:public JavaScript{
public:
  JSUpdateEclipse(Eclipse* eclipse) : eclipse_(eclipse){}
  virtual std::string execute();
private:
  Eclipse* eclipse_;
};

class JSDeleteEclipse : public JavaScript{
public:
  JSDeleteEclipse(unsigned long long id) : id_(id){}
  virtual std::string execute();
private:
  unsigned long long id_;
};

class JSClearEclipse : public JavaScript{
public:
  virtual std::string execute();
};

} //namespace tools

#endif // WEBKIT_H