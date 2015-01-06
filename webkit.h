#ifndef WEBKIT_H
#define WEBKIT_H

#include <cstring>
#include <sstream>

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

#endif // WEBKIT_H
