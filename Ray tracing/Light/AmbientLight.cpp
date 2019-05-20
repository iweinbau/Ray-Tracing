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
#include "../Builder/World.hpp"
#include <random>

Vect3 AmbientLight::getDirection(Hitinfo& hitinfo){
    Vect3 w = hitinfo.normal;
    Vect3 u = Vect3(0.00424, 1, 0.00764).cross(w);
    u.normalize();
    Vect3 v = u.cross(w);
    
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(0.0, 1.0);
    
    //From raytracing from the ground up.
    double x = dis(gen);
    double y = dis(gen);
    
    double cos_phi = cos(2.0 * PI * x);
    double sin_phi = sin(2.0 * PI * x);
    double cos_theta = pow((1.0 - y), 1.0 / (1.0 + 1.0));
    double sin_theta = sqrt (1.0 - cos_theta * cos_theta);
    
    double pu = sin_theta * cos_phi;
    double pv = sin_theta * sin_phi;
    double pw = cos_theta;
    
    return u * pu + v * pv + w * pw;

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
        if (obj->hit(ray,intersection, t,normal)) {
            return true;
        }
    }
    return false;
}
