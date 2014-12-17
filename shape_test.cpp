#include "shape.h"
#include <cassert>
#include <cmath>
#include <iostream>

namespace tools{

bool Equal(double, double);

class Test{
public:
  void RunAllTest(){
    FunctionShape(); 
    FunctionCircle(); 
    FunctionEclipse();
    //FunctionTest();
    FunctionTestEclipse();
  } 
  
  void FunctionShape(){
    double data[20][3];
    for(int i = -20; i!=20; ++i){
      for(int j = -20; j != 20; ++j){
        Shape2D* line = new Line2D(Point2D(i, j));
        for(int k = 0; k <= line->GetLength(); ++k){
          Point2D temp(0.0, 0.0);
          line->GetPoint(k, temp);
          if(i == 0 && j == 0){
            continue;
          }
          assert(Equal(temp.x, i*k/line->GetLength()));
          assert(Equal(temp.x, j*k/line->GetLength()));
        }
        assert(Equal(line->GetLength(), sqrt(i*i + j*j)));   
        delete line;
      }
    }
  }

  void FunctionCircle(){
    double data[20][3];
    for(int i = -20; i!=20; ++i){
      for(int j = -20; j != 20; ++j){
        for(int k = -6; k <= 6; ++k){
          if((i == 0 && j == 0) || k == 0){
            continue;
          }
          Shape2D* line = new Circle2D(Point2D(i, j), k);
          Point2D temp(0.0, 0.0);
         line->GetPoint(fabs(k), temp);
          double radius = sqrt(i*i + j*j);
          assert(Equal(temp.x, i - radius*cos(k)));
          assert(Equal(temp.y, j + radius*sin(k)));
          assert(Equal(line->GetLength(), k*sqrt(i*i + j*j)));   
          delete line;
        }
      }
    }
  }

  void FunctionEclipse(){
    for(int major_x = -20; major_x != 20; ++major_x){
      for(int major_y = -20; major_y != 20; ++major_y){
        for(int minor_x = -20; minor_x !=20; ++minor_x){
          for(int minor_y = -20; minor_y != 20; ++minor_y){
            for(int angle_i = -6; angle_i !=6; ++angle_i){
              if((major_x == 0 && major_y == 0) 
                  || (minor_x == 0 && minor_y == 0)
                  || (Equal(minor_x, major_x) 
                      && Equal(minor_y, major_y))
                  || angle_i == 0){
                continue;
              }
              Shape2D *eclipse = new Eclipse2D(Point2D(major_x, major_y), 
                  Point2D(minor_x, minor_y), angle_i);
              double major_radius = sqrt(major_x*major_x + major_y*major_y);
              double minor_radius = sqrt(pow(major_x-minor_x, 2) 
                  + pow(major_y-minor_y, 2));
              double average_radius = (major_radius + minor_radius) / 2;
              assert(Equal(eclipse->GetLength(),  angle_i*average_radius));
              Point2D temp(0.0, 0.0);
             eclipse->GetPoint(fabs(angle_i), temp);
              assert(Equal(temp.x, major_x-major_radius*cos(angle_i)));
              assert(Equal(temp.y, minor_x+minor_radius*sin(angle_i)));
              delete eclipse;
            }
          }
        }
      }
    } 
  }

  void FunctionTest(){
    Shape2D *circle = new Circle2D(Point2D(40, 40), -2*M_PI+0.000001);
    float dot = 2*3.1415265/40.0;
    for(int i=1; i!=41; ++i){
      Point2D point(0.0, 0.0);
      circle->GetPoint(dot*i*40*1.41421356, point);
      std::cout << dot*i << ": " << point.x << ", " << point.y << std::endl;
    }
  }


  void FunctionTestEclipse(){
    Eclipse2D* circle = new Eclipse2D(Point2D(40, 40), Point2D(20, 60), -2*M_PI+0.000001);
    float dot = 2*3.1415265/40.0;
    for(int i=1; i!=41; ++i){
      Point2D point(0.0, 0.0);
      circle->GetPoint(dot*i*40*1.41421356, point);
      std::cout << dot*i << ": " << point.y << ", " << point.y << std::endl;
    }
  }

  bool Equal(double lhs, double rhs){
    if( lhs - rhs < 0.000001 || lhs - rhs > -0.000001 )
      return true;
    else
      return false;
  }  
};

} //namespace tools

int main(int argc, char** argv){
    tools::Test().RunAllTest();
    return 0;
}

