//
//  Instance.cpp
//  raytracer
//
//  Created by Iwein Bau on 22/03/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#include "Instance.hpp"

Instance::Instance():Object(),object(),invTransform(){}

Instance::Instance(Object* obj,Material* mat):Object(mat),object(obj),invTransform(){}

Instance::~Instance(){}

void
Instance::translate(Vect3 const& translate) {
    
    Matrix4 inv_translation_matrix;
    
    inv_translation_matrix.elements[0][3] = -translate.x_;
    inv_translation_matrix.elements[1][3] = -translate.y_;
    inv_translation_matrix.elements[2][3] = -translate.z_;
    
    invTransform = invTransform * inv_translation_matrix;
}

void Instance::scale(Vect3 const& scale){
    Matrix4 inv_scale_matrix;
    
    inv_scale_matrix.elements[0][0] = 1/scale.x_;
    inv_scale_matrix.elements[1][1] = 1/scale.y_;
    inv_scale_matrix.elements[2][2] = 1/scale.z_;
    
    invTransform = invTransform * inv_scale_matrix;
}

bool Instance::hit(Ray const& ray, Point3& intersection, double& tmin,Normal& normal){
    Ray inv_ray(ray);
    inv_ray.direction_ = invTransform * ray.direction_;
    inv_ray.origin_ = invTransform * ray.origin_;
    
    if(object->hit(inv_ray, intersection, tmin,normal)){
        intersection = ray.origin_ + ray.direction_ * tmin;
        normal.normalize();
        return true;
    }
    return false;
}


