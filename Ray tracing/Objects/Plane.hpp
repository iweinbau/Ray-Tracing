//
//  Plane.hpp
//  Ray-tracer
//
//  Created by Iwein Bau on 17/12/2018.
//  Copyright © 2018 Iwein Bau. All rights reserved.
//

#ifndef Plane_h
#define Plane_h

#include "../Utils/Vect3.hpp"
#include "Object.hpp"
#include "../Utils/Normal.hpp"



class Plane : public Object {
public:
    Plane():
    Object()
    {}

    Plane(Point3 position, Normal normal,Material* shader):
    Object(position,shader),
    normal_(normal.normalize()){}

    Plane(Point3 position, Normal normal):
    Object(position),
    normal_(normal.normalize()){}

    Plane(Plane const& plane):
    Object(plane.position,plane.shader_),
    normal_(plane.normal_)
    {}

    virtual bool hit(Ray const& ray, Point3& intersection, double& tmin,Normal& normal){
        float t = (Vect3(position - ray.origin_)).dot(normal_) / (ray.direction_.dot(normal_));

        if (t > kEpsilon) {
            tmin = t;
            intersection = ray.origin_ + (ray.direction_ * t);
            normal = normal_;
            return (true);
        }

        return(false);
    };
    Box caluclateBoundingBox(){
      return Box();
    };


public:
    Normal normal_;
};

#endif /* Plane_h */
