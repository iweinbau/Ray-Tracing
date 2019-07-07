//
//  AmbientLight.cpp
//  raytracer
//
//  Created by Iwein Bau on 20/05/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#include "AmbientLight.hpp"
#include "../Utils/Constants.hpp"
#include "../Utils/Hitinfo.hpp"
#include "../Utils/Normal.hpp"
#include "../Objects/Object.hpp"
#include "../Utils/Point3.hpp"
#include "../Builder/World.hpp"
#include <random>

Vect3 AmbientLight::getDirection(Hitinfo& hitinfo){
    Vect3 w = hitinfo.normal;
    Vect3 u = Vect3(0.00424, 1, 0.00764).cross(w);
    u = u.normalize();
    Vect3 v = u.cross(w);
    
    Point3 p = sampler.sampleOnHemisphere();
    
    Vect3 wi = u * p.x_ + v * p.y_ + w * p.z_;
    return wi.normalize();

}

Vect3 AmbientLight::getIntensity(Hitinfo& hitinfo,World& world){
    //Get direction, cast ray if hit object then we are in shadow.
    Ray shadow_ray(hitinfo.point,getDirection(hitinfo));
    if(shadow_hit(shadow_ray,world)){
        return color_ * i_ * factor;
    }
    return color_ * i_;
}

bool AmbientLight::shadow_hit(Ray const& ray,World& world){
    double t;
    Point3 intersection;
    Normal normal;
    for(Object* obj : world.objects){
        if (obj->hit(ray,intersection, t,normal)&&obj->shadow_cast) {
            return true;
        }
    }
    return false;
}
