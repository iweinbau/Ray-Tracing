//
//  Rectangle.cpp
//  raytracer
//
//  Created by Iwein Bau on 01/05/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#include "Rectangle.hpp"
#include <random>

Rectangle::Rectangle():Object(){}
Rectangle::Rectangle(Point3 p0,Vect3 v1, Vect3 v2):
        Object(),
        p0(p0),
        n(v1.cross(v2).normalize()),
        a(v1),
        b(v2)
{}
Rectangle::Rectangle(Point3 p0, Vect3 v1, Vect3 v2,Material* mat):
    Object(mat),
    p0(p0),
    n(v1.cross(v2).normalize()),
    a(v1),
    b(v2)
{}
Rectangle::~Rectangle(){};

Rectangle::Rectangle(Rectangle const& rect):Object(rect),
p0(rect.p0),
n(rect.n),
a(rect.a),
b(rect.b){}


Box Rectangle::caluclateBoundingBox(){
    return Box(Point3(std::min(p0.x_, p0.x_ + a.x_ + b.x_) - kEpsilon,
                      std::min(p0.y_, p0.y_ + a.y_ + b.y_) - kEpsilon,
                      std::min(p0.z_, p0.z_ + a.z_ + b.z_) - kEpsilon),
              Point3(std::max(p0.x_, p0.x_ + a.x_ + b.x_) + kEpsilon,
                     std::max(p0.y_, p0.y_ + a.y_ + b.y_) + kEpsilon,
                     std::max(p0.z_, p0.z_ + a.z_ + b.z_) + kEpsilon));
}

bool Rectangle::hit(Ray const& ray, Point3& intersection, double& tmin,Normal& normal){
    float t = (Vect3(p0 - ray.origin_)).dot(n) / (ray.direction_.dot(n));

    if(t <= kEpsilon){
        return false;
    }
    
    Point3 p = ray.origin_ + t * ray.direction_;
    Vect3 d = p - p0;
    
    double ddota = d.dot(a);
    if(ddota < 0 || ddota > a.length()*a.length())
        return false;
    double ddotb = d.dot(b);
    if(ddotb < 0 || ddotb > b.length()*b.length())
        return false;
    
    tmin = t;
    normal = n;
    intersection= d;
    return true;
    
}
Vect3 Rectangle::sample(){
    
    double x = sampler.sample();
    double y = sampler.sample();
    
    return p0 + a * x + b * y;
}
Normal Rectangle::getNormal(Vect3 const& point){
    return n;
}
double Rectangle::pdf(){
    return 1/a.length() * b.length();
}
