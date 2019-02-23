//
//  Plane.hpp
//  Ray-tracer
//
//  Created by Iwein Bau on 17/12/2018.
//  Copyright © 2018 Iwein Bau. All rights reserved.
//

#ifndef Plane_h
#define Plane_h

#include "../vector3f.hpp"

class Plane : public Object {
public:
    Plane():
    Object()
    {}
    
    Plane(Vect3 position, Vect3 normal,Material* shader):
    Object(position,shader),
    normal(normal)
    {
        
    }
    
    Plane(Plane const& plane):
    Object(plane.position,plane.shader_),
    normal(plane.normal)
    {}
    
    virtual bool hit(Ray& ray, Vect3& intersection, double& tmin){
        float t = (position - ray.origin_).dot(normal) / (ray.direction_.dot(normal));
        
        if (t > kEpsilon) {
            tmin = t;
            intersection = ray.origin_ + (ray.direction_ * t);
            
            return (true);
        }
        
        return(false);
    };
    
    virtual Vect3 getNormalAtPoint(Vect3 point){
        return normal;
    };
    
    
public:
    Vect3 normal;
};

#endif /* Plane_h */
