//
//  AreaLight.cpp
//  raytracer
//
//  Created by Iwein Bau on 01/05/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#include "AreaLight.hpp"

#include "../Objects/Object.hpp"
#include "../Utils/Hitinfo.hpp"
#include "../Builder/World.hpp"


AreaLight::AreaLight(Object* object,Vect3 color,double i):Light(color,i),obj(object){}

AreaLight::AreaLight(AreaLight const& l):Light(l){}

AreaLight::~AreaLight(){
    // Do not delete object, this will be deleted in the world.
}

Vect3 AreaLight::getDirection(Hitinfo& hitinfo){
    //get point on surface.
    samplePoint = obj->sample();
    normal = obj->getNormal(samplePoint);
    direction = (samplePoint - hitinfo.point).normalize();
    
    return direction;
}

Vect3 AreaLight::getIntensity(Hitinfo& hitinfo,World& world){
    double ddotn = (direction.neg().dot(normal));
    if(ddotn < 0){
        return Vect3(0);
    }
    double d = (samplePoint - hitinfo.point).length();
    double G = ddotn / (d *d);
    return (color_ * i_ * G) / obj->pdf();
}

bool AreaLight::shadow_hit(Ray const& ray,World& world){
    double t;
    double maxt = (samplePoint - ray.origin_).length();
    Point3 intersection;
    Normal normal;
    for(Object* obj : world.objects){
        if (obj->hit(ray,intersection, t,normal) && obj->shadow_cast) {
            if(t < maxt){
                return true;
            }
        }
    }
    return false;
}
