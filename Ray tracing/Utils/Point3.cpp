//
//  Point3.cpp
//  raytracer
//
//  Created by Iwein Bau on 22/03/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#include <stdio.h>

#include "Point3.hpp"

Point3::Point3():x_(0),y_(0),z_(0)
{}

Point3::Point3(Vect3 vect):x_(vect.x_),y_(vect.y_),z_(vect.z_)
{}

Point3::Point3(double x, double y, double z):x_(x),y_(y),z_(z)
{}

Point3::Point3(Point3 const &v):x_(v.x_),y_(v.y_),z_(v.z_)
{}

Point3::~Point3(){}
Point3& Point3::operator= (Point3 const& v){
    x_ = v.x_; y_ = v.y_; z_=v.z_;
    return(*this);
}

Point3 Point3::neg() const{
    return Point3(-x_,-y_,-z_);
}
