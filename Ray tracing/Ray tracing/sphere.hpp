//
//  sphere.hpp
//  Ray-tracer
//
//  Created by Iwein Bau on 16/12/2018.
//  Copyright © 2018 Iwein Bau. All rights reserved.
//

#ifndef sphere_h
#define sphere_h

class Phong;

#include "material.hpp"
#include "vector3f.hpp"
#include "ray.hpp"

class Sphere{
public:
    double kEpsilon = 0.001;
    double radius_;
    Vect3 center_;
    Phong* shader_;
    
    Sphere()
    {}
    
    Sphere(Vect3 position, double radius,Phong* material):
    center_(position), shader_(material),radius_(radius)
    {}
    
    Sphere(Sphere const& sphere):
    radius_(sphere.radius_),center_(sphere.center_),shader_(sphere.shader_)
    {}
    
    Sphere& operator= (Sphere const& sphere){
        if(this == &sphere)
            return (*this);
        
        center_ = sphere.center_;
        radius_ = sphere.radius_;
        shader_ = sphere.shader_;
        return (*this);
    }
    
    bool hit(Ray& ray, Vect3& intersection, double& tmin){
        double t;
        Vect3    temp     = ray.origin_ - center_;
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
        return (point - center_).normalize();
    }
};
#endif /* sphere_h */
