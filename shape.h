#ifndef SHAPE_H_
#define SHAPE_H_

#include <cmath>

namespace tools{

struct Point2D{
  Point2D():x(0.0),y(0.0){}
  Point2D(double a,long double b):x(a), y(b){}
  double x;
  double y;
};

struct PointState2D{
  Point2D point;
  float speed;
  float acc;
  long long tick;
  long long time;
};

class Shape2D{
public:
  virtual double GetLength() const = 0;
  //length >= 0 and less than GetLength() or equal GetLength()
  virtual void GetPoint(double length, Point2D& point) const = 0;
};

//Point2D cannot be {0.0, 0.0}
class Line2D : public Shape2D{
public:
  // line cannot equal {0.0, 0.0}
  Line2D(const Point2D& line):line_(line){}
  virtual double GetLength() const;
  virtual void GetPoint(double length, Point2D& point) const;
private:
  Point2D line_;    //vector of line
};

class Circle2D: public Shape2D{
public:
  //p cannot be {0.0, 0.0}, angle is greater than -2*PI and less than 2*PI 
  Circle2D(const Point2D &p, float angle) : center_(p), angle_(angle), radius_(Length(center_)){
    //angle_bise_ = M_PI + Angle( p.longitude, p.latitude);
  }
  virtual double GetLength() const;
  virtual void GetPoint(double length, Point2D& point) const;

private:
  Point2D center_;  //vector from start point to radius
  float angle_; //the angle that neet to cut, plus stant for clock direction, or un-clock direction
  //float angle_bise_;

  double radius_;

  double Length(const Point2D& p) const;
  //Angle return [0,2*PI]
  double Angle(double x, double y) const;
};

class Eclipse2D : public Shape2D{
public:
  virtual double GetLength() const;
  virtual void GetPoint(double length, Point2D& point) const;

  //major cannot be {0.0, 0.0}, minor cannot be equal to major and {0.0 , 0.0}
  //angle must be greater than -2*PI and less than 2*PI
  Eclipse2D(const Point2D& major, const Point2D& minor, float angle)
    :semi_major_(major), semi_minor_(minor), angle_(angle){
  }
private:
  Point2D semi_major_;
  Point2D semi_minor_;
  float angle_;

  double Length(const Point2D& p) const;
  double Angle(double x, double y) const;
};

}   //namespace tools

#endif //SHAPE_H_
