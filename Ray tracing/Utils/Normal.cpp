//
//  Normal.cpp
//  raytracer
//
//  Created by Iwein Bau on 22/03/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#include "Normal.hpp"
#include "Point3.hpp"

Normal::Normal():x_(0),y_(0),z_(0)
{}

Normal::Normal(double x, double y, double z):x_(x),y_(y),z_(z)
{}

Normal::Normal(Normal const &v):x_(v.x_),y_(v.y_),z_(v.z_)
{}

Normal::Normal(Point3 const& p):x_(p.x_),y_(p.y_),z_(p.z_){}

Normal::Normal(Vect3 const& v):x_(v.x_),y_(v.y_),z_(v.z_){}


Normal::~Normal(){}
Normal& Normal::operator= (Normal const& v){
    x_ = v.x_; y_ = v.y_; z_=v.z_;
    return(*this);
}

double Normal::length() {
    return (sqrt(x_ * x_ + y_ * y_ + z_ * z_));
}

Normal Normal::normalize() {
    double mag = length();
    return Normal(x_ /mag, y_ / mag, z_ /mag);
}

Normal Normal::neg() const{
    return Normal(-x_,-y_,-z_);
}

double Normal::dot(Normal const& other) const {
    return(x_ * other.x_ + y_ * other.y_ + z_ * other.z_);
}

Normal Normal::cross(Normal other) {
    double x = y_ * other.z_ - z_ * other.y_;
    double y = z_ * other.x_ - x_ * other.z_;
    double z = x_ * other.y_ - y_ * other.x_;
    
    return Normal(x, y, z);
}
