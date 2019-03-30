#include "Box.hpp"

Box::Box(const Point3& p1, const Point3& p2):p1(p1),p2(p2){}
Box::Box(){}
Box::~Box(){}

Point3* Box::getVertices(Point3 v[8]){
    v[0] = p1;
    v[1] = Point3(p2.x_,p1.y_,p1.z_);
    v[2] = Point3(p2.x_,p2.y_,p1.z_);
    v[3] = Point3(p1.x_,p2.y_,p1.z_);
    
    v[4] = p2;
    v[5] = Point3(p1.x_,p2.y_,p2.z_);
    v[6] = Point3(p1.x_,p1.y_,p2.z_);
    v[7] = Point3(p2.x_,p2.y_,p2.z_);
    
    return v;
}

bool Box::hit(Ray const& ray){
  return false;
}

