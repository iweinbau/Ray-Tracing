//
//  Object.hpp
//  Ray-tracer
//
//  Created by Iwein Bau on 17/12/2018.
//  Copyright © 2018 Iwein Bau. All rights reserved.
//

#ifndef Object_h
#define Object_h

#include "../vector3f.hpp"
#include "../ray.hpp"

class Material;

class Object{
public:
    const double kEpsilon = 0.00001;
    Object():
    position(Vect3())
    {}
    
    Object(Vect3 position,Material* material):
    position(position),
    shader_(material)
    {}

    Object(Object const& obj):
    position(obj.position),
    shader_(obj.shader_)
    {}
    
    Object& operator= (Object const& obj){
        if(this == &obj)
            return (*this);
        
        position = obj.position;
        shader_ = obj.shader_;
        return (*this);
    }
    
    virtual bool hit(Ray& ray, Vect3& intersection, double& tmin) = 0;
    
    virtual Vect3 getNormalAtPoint(Vect3 point) = 0;
    
public:
    Material* shader_;
    Vect3 position;
    
};

#endif /* Object_h */
