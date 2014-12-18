#include "shape.h"

#include <cmath>
#include <cstddef>
#include <cassert>

namespace tools{

//本算法基于二维平面实现的

bool Equal(double lhs_std, double rhs){
  if(lhs_std - rhs < 0.0000001 && lhs_std - rhs > -0.00000000000001)
    return true;
  else
    return false;
}

double Line2D::GetLength() const{
  return sqrt(pow(line_.x, 2) + pow(line_.y, 2));
}

void Line2D::GetPoint(double length, Point2D& point) const{
  assert( (length < GetLength() &&  length > 0 ) || 
      ( Equal(length, GetLength()) || Equal(length, 0) ));
  double radix = length / GetLength();
  point.x = radix*line_.x;
  point.y = radix*line_.y;
}

double Circle2D::Angle(double x, double y) const{
  assert(!(Equal(x, 0.0) && Equal(y, 0.0)));
  if( Equal(x, 0.0) && y > 0.0 )
    return M_PI / 2;
  if( Equal(x, 0.0) && y < 0.0 )
    return 3*M_PI / 2;
  if(Equal(y, 0.0) && x > 0.0)
    return 0.0;
  if(Equal(y, 0.0 ) && x < 0.0)
    return M_PI;
  if( x > 0.0 && y > 0.0 )
    return atan(y/x);
  if(x < 0.0 && y > 0.0)
    return M_PI + atan(y/x);
  if(x < 0.0 && y < 0.0 )
    return M_PI + atan(y/x);
  if(x > 0.0 && y < 0.0 )
    return 2*M_PI + atan(y/x);
  return 0.0;
}

double Circle2D::Length(const Point2D& p) const{
  return sqrt(pow(p.x, 2) + pow(p.y, 2));
}

double Circle2D::GetLength() const{
  assert(angle_ < 2*M_PI && angle_ > -2*M_PI);
  return fabs(angle_)*radius_;
}

void Circle2D::GetPoint(double length, Point2D& point) const{
  assert((length > 0 && length < GetLength())
  || Equal(length, 0.0) || Equal(length, GetLength()));
  if(Equal(length, 0.0)){
    point.x = 0.0;
    point.y = 0.0;
    return;
  }
  float current_angle = length / radius_;
  double x = radius_ - radius_ * cos(current_angle);
  double y = radius_ * sin(current_angle);
  y = angle_ < 0 ? -y : y;
  double radius_temp = Length(Point2D(x, y));
  double angle_bise = Angle(x, y) 
    + Angle(center_.x, center_.y);
  x = radius_temp*cos(angle_bise);
  y = radius_temp*sin(angle_bise);
  point.x = x;
  point.y = y;
}

double Eclipse2D::Length(const Point2D& p) const{
  return sqrt(pow(p.x, 2) + pow(p.y, 2));
}
double Eclipse2D::GetLength() const{
  //TODO: something
  double major = Length(semi_major_);
  Point2D p(semi_minor_.x- semi_major_.x,  
      semi_minor_.y- semi_major_.y);
  double minor = Length(p);
  return fabs(angle_)*(major + minor)/2;
}

void Eclipse2D::GetPoint(double length, Point2D& point) const{
  assert((length > 0 && length < GetLength()) 
      || Equal(length, 0.0) || Equal(length, GetLength()));
  if(Equal(length, 0.0)){
    point.x = 0.0;
    point.y = 0.0;
    return;
  }
  double major = Length(semi_major_);
  Point2D p(semi_minor_.x- semi_major_.x,  
      semi_minor_.y - semi_major_.y);
  double minor = Length(p);
  float current_angle = length / (major + minor) * 2;
  double x = semi_major_.x - major*cos(current_angle);
  double y = minor*sin(current_angle);
  double radius_temp = Length(Point2D(x, y));
  double angle_bise = Angle(x, y) 
    + Angle(semi_major_.x , semi_major_.y);
  x = radius_temp*cos(angle_bise);
  y = radius_temp*sin(angle_bise);
  point.x = x;
  point.y = y;
}

double Eclipse2D::Angle(double x, double y) const{
  assert(!(Equal(x, 0.0) && Equal(y, 0.0)));
  if( Equal(x, 0.0) && y > 0.0 )
    return M_PI / 2;
  if( Equal(x, 0.0) && y < 0.0 )
    return 3*M_PI / 2;
  if(Equal(y, 0.0) && x > 0.0)
    return 0.0;
  if(Equal(y, 0.0 ) && x < 0.0)
    return M_PI;
  if( x > 0.0 && y > 0.0 )
    return atan(y/x);
  if(x < 0.0 && y > 0.0)
    return M_PI + atan(y/x);
  if(x < 0.0 && y < 0.0 )
    return M_PI + atan(y/x);
  if(x > 0.0 && y < 0.0 )
    return 2*M_PI + atan(y/x);
  return 0.0;
}
} //namespace tools
