//
//  Point3.cpp
//  raytracer
//
//  Created by Iwein Bau on 22/03/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#include <stdio.h>

#include "Point3.hpp"

Point3::Point3():Vect3()
{}

Point3::Point3(Vect3 vect):Vect3(vect)
{}

Point3::Point3(double x, double y, double z):Vect3(x,y,z)
{}

Point3::Point3(Point3 const &v):Point3(v.x_,v.y_,v.z_)
{}

Point3::~Point3(){}

Point3& Point3::operator= (Point3 const& v){
    x_ = v.x_; y_ = v.y_; z_=v.z_;
    return(*this);
}
