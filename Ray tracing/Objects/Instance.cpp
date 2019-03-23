//
//  Instance.cpp
//  raytracer
//
//  Created by Iwein Bau on 22/03/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#include "Instance.hpp"

Instance::Instance():Object(),object(),transform(){}

Instance::Instance(Object* obj,Material* mat):Object(mat),object(obj),transform(){}

Instance::~Instance(){}

void Instance::translate(Vect3 const& translate) {
    transform.translate(translate);
}

void Instance::scale(Vect3 const& scale){
    transform.scale(scale);
}

bool Instance::hit(Ray const& ray, Point3& intersection, double& tmin,Normal& normal){
    Ray inv_ray(ray);
    inv_ray.direction_ = transform.globalToLocal(ray.direction_);
    inv_ray.origin_ = transform.globalToLocal(ray.origin_);
    
    if(object->hit(inv_ray, intersection, tmin,normal)){
        intersection = transform.localToGlobal(intersection);
        normal = transform.localToGlobal(normal);
        normal = normal.normalize();
        return true;
    }
    return false;
}


