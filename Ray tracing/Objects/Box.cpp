#include "Box.hpp"
Box::Box(const Point3& p1, const Point3& p2):p1(p1),p2(p2){}
Box::Box(){}
Box::~Box(){}

bool Box::hit(Ray const& ray){
  return false;
}
