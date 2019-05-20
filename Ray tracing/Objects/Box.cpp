#include "Box.hpp"
#include "../Utils/Constants.hpp"

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
bool Box::inside(Point3 const& p){
    return ((p.x_ >= p1.x_ && p.x_ <= p2.x_) && (p.y_ >= p1.y_ && p.y_ <= p2.y_) && (p.z_ >= p1.z_ && p.z_ <= p2.z_));
}
bool Box::hit(Ray const& ray,double& t){
    double ox = ray.origin_.x_; double oy = ray.origin_.y_; double oz = ray.origin_.z_;
    double dx = ray.direction_.x_; double dy = ray.direction_.y_; double dz = ray.direction_.z_;
    
    double tx_min, ty_min, tz_min;
    double tx_max, ty_max, tz_max;
    
    double a = 1.0 / dx;
    if (a >= 0) {
        tx_min = (p1.x_ - ox) * a;
        tx_max = (p2.x_ - ox) * a;
    }
    else {
        tx_min = (p2.x_ - ox) * a;
        tx_max = (p1.x_ - ox) * a;
    }
    
    double b = 1.0 / dy;
    if (b >= 0) {
        ty_min = (p1.y_ - oy) * b;
        ty_max = (p2.y_ - oy) * b;
    }
    else {
        ty_min = (p2.y_ - oy) * b;
        ty_max = (p1.y_ - oy) * b;
    }
    
    double c = 1.0 / dz;
    if (c >= 0) {
        tz_min = (p1.z_ - oz) * c;
        tz_max = (p2.z_ - oz) * c;
    }
    else {
        tz_min = (p2.z_ - oz) * c;
        tz_max = (p1.z_ - oz) * c;
    }
    
    double t0, t1;
    
    // find largest entering t value
    
    if (tx_min > ty_min)
        t0 = tx_min;
    else
        t0 = ty_min;
    
    if (tz_min > t0)
        t0 = tz_min;
    
    // find smallest exiting t value
    
    if (tx_max < ty_max)
        t1 = tx_max;
    else
        t1 = ty_max;
    
    if (tz_max < t1)
        t1 = tz_max;
    
    bool hit (t0 < t1 && t1 > kEpsilon);
    t = t1;
    return hit;
}

