//
//  sphere.hpp
//  Ray-tracer
//
//  Created by Iwein Bau on 16/12/2018.
//  Copyright © 2018 Iwein Bau. All rights reserved.
//

#ifndef sphere_h
#define sphere_h

#include "../Sampler/Sampler.hpp"
class Material;

#include <random>


#include "../Utils/Vect3.hpp"
#include "../Utils/Normal.hpp"
#include "Object.hpp"
#include "../Utils/ray.hpp"


class Sphere : public Object{
public:
    double radius_;

    Sphere():Object()
    {}

    Sphere(Point3 position, double radius, Material* material):
    Object(material),radius_(radius),position(position)
    {}

    Sphere(Point3 position, double radius):
    Object(),position(position),radius_(radius)
    {}

    Sphere(Sphere const& sphere):
    Object(sphere.shader_),
    position(sphere.position),
    radius_(sphere.radius_)
    {}

    Sphere& operator= (Sphere const& sphere){
        if(this == &sphere)
            return (*this);

        Object::operator=(sphere);
        
        position = sphere.position;
        radius_ = sphere.radius_;
        return (*this);
    }

    bool hit(Ray const& ray, Point3& intersection, double& tmin,Normal& normal){
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
                normal = Normal(Vect3(intersection - position).normalize());
                return (true);
            }

            t = (-b + e) / denom;    // larger root

            if (t > kEpsilon) {
                tmin = t;
                intersection = ray.origin_ + (ray.direction_ * t);
                normal = Normal(Vect3(intersection - position).normalize());
                return (true);
            }
        }

        return (false);
    }
    
    Vect3 sample(){
        double r1 = sampler.sample(),r2 = sampler.sample();
        
        double theta = 2 * PI * r1;
        double phi = acos(1 - 2 * r2);
        double x = radius_ * sin(phi) * cos(theta);
        double y = radius_ * sin(phi) * sin(theta);
        double z = radius_ * cos(phi);
        
        return Vect3(x,y,z) + position;
    }
    
    double pdf(){
        return 1/(4 * PI * radius_ *radius_);
    }
    
    Normal getNormal(Vect3 const& point){
        return (point - position).normalize();
    }

    Box caluclateBoundingBox(){
      return Box(Point3(position - radius_), Point3(position + radius_));
    };
private:
    Sampler sampler;
    Point3 position;
};
#endif /* sphere_h */
