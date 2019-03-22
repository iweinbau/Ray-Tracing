//
//  Vect3.cpp
//  raytracer
//
//  Created by Iwein Bau on 22/03/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#include <stdio.h>

#include "Vect3.hpp"
#include "Point3.hpp"
#include "Normal.hpp"

Vect3::Vect3():x_(0),y_(0),z_(0)
{}

Vect3::Vect3(double x):x_(x),y_(x),z_(x){}

Vect3::Vect3(double x, double y, double z):x_(x),y_(y),z_(z)
{}

Vect3::Vect3(Vect3 const &v):x_(v.x_),y_(v.y_),z_(v.z_)
{}

Vect3::Vect3(Point3 const& p):x_(p.x_),y_(p.y_),z_(p.z_){}

Vect3::Vect3(Normal const& n):x_(n.x_),y_(n.y_),z_(n.z_){}

Vect3::~Vect3(){}
Vect3& Vect3::operator= (Vect3 const& v){
    x_ = v.x_; y_ = v.y_; z_=v.z_;
    return(*this);
}

double Vect3::length() {
    return (sqrt(x_ * x_ + y_ * y_ + z_ * z_));
}

Vect3 Vect3::normalize() {
    double mag = length();
    return Vect3(x_ /mag, y_ / mag, z_ /mag);
}

Vect3 Vect3::neg() const{
    return Vect3(-x_,-y_,-z_);
}

double Vect3::dot(Vect3 const& other) const {
    return(x_ * other.x_ + y_ * other.y_ + z_ * other.z_);
}

Vect3 Vect3::cross(Vect3 other) {
    double x = y_ * other.z_ - z_ * other.y_;
    double y = z_ * other.x_ - x_ * other.z_;
    double z = x_ * other.y_ - y_ * other.x_;
    
    return Vect3(x, y, z);
}
