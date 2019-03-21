//
//  sphere.hpp
//  Ray-tracer
//
//  Created by Iwein Bau on 16/12/2018.
//  Copyright © 2018 Iwein Bau. All rights reserved.
//

#ifndef sphere_h
#define sphere_h

class Material;

#include "../Utils/Vect3.hpp"
#include "Object.hpp"
#include "../Utils/ray.hpp"


class Sphere : public Object{
public:
    const double kEpsilon = 0.001;
    double radius_;
    
    Sphere():Object()
    {}
    
    Sphere(Vect3 position, double radius, Material* material):
    Object(position,material),radius_(radius)
    {}
    
    Sphere(Sphere const& sphere):
    Object(sphere.position,sphere.shader_),
    radius_(sphere.radius_)
    {}
    
    Sphere& operator= (Sphere const& sphere){
        if(this == &sphere)
            return (*this);
        
        Object::operator=(sphere);
        
        radius_ = sphere.radius_;
        return (*this);
    }
    
    bool hit(Ray const& ray, Vect3& intersection, double& tmin){
        double t;
        Vect3    temp     = ray.origin_ - position;
        double         a         = ray.direction_.dot(ray.direction_);
        double         b         = 2 * temp.dot(ray.direction_);
        double         c         = temp.dot(temp) - radius_ * radius_;
        double         disc    = b * b - 4.0 * a * c;
        
        if (disc < 0.0)
            return(false);
        else {
            double e = sqrt(disc);
            double denom = 2.0 * a;
            t = (-b - e) / denom;    // smaller root
            
            if (t > kEpsilon) {
                tmin = t;
                intersection = ray.origin_ + (ray.direction_ * t);
                return (true);
            }
            
            t = (-b + e) / denom;    // larger root
            
            if (t > kEpsilon) {
                tmin = t;
                intersection = ray.origin_ + (ray.direction_ * t);
                return (true);
            }
        }
        
        return (false);
    }
    
    Vect3 getNormalAtPoint(Vect3 point) {
        return (point - position).normalize();
    }
};
#endif /* sphere_h */
