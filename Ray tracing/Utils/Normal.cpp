//
//  Normal.cpp
//  raytracer
//
//  Created by Iwein Bau on 22/03/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#include "Normal.hpp"
#include "Vect3.hpp"
#include "Point3.hpp"

Normal::Normal():Vect3()
{}

Normal::Normal(double x, double y, double z):Vect3(x,y,z)
{}

Normal::Normal(Normal const &v):Vect3(v.x_,v.y_,v.z_)
{}

Normal::Normal(Point3 const& p):Vect3(p.x_,p.y_,p.z_){}

Normal::Normal(Vect3 const& v):Vect3(v)
{}

Normal::~Normal(){}
                                      
Normal& Normal::operator= (Normal const& v){
    x_ = v.x_; y_ = v.y_; z_=v.z_;
    return(*this);
}
