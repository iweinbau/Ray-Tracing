//
//  Hitinfo.hpp
//  Ray-tracer
//
//  Created by Iwein Bau on 17/12/2018.
//  Copyright © 2018 Iwein Bau. All rights reserved.
//
#ifndef Hitinfo_h
#define Hitinfo_h

#include "Vect3.hpp"
#include "Point3.hpp"

class Hitinfo{
public:
    Hitinfo()
    {}

    Hitinfo(Vect3& normal, Point3& point, Vect3& direction,double distance):
    normal(normal),
    point(point),
    direction(direction),
    d(distance)
    {}

    ~Hitinfo()
    {}

    double d;
    Vect3 normal;
    Point3 point;
    Vect3 direction;

};

#endif /* Hitinfo_h */
