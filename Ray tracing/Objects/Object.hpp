//
//  Object.hpp
//  Ray-tracer
//
//  Created by Iwein Bau on 17/12/2018.
//  Copyright © 2018 Iwein Bau. All rights reserved.
//

#ifndef Object_h
#define Object_h


#include "../Utils/Constants.hpp"
#include "../Utils/Vect3.hpp"
#include "../Utils/Point3.hpp"
#include "../Utils/ray.hpp"
#include "../Utils/Normal.hpp"
#include "./Box.hpp"

class Material;


class Object{
public:
    Object(){}

    Object(Material* material):
    shader_(material)
    {}

    Object(Object const& obj):
    shader_(obj.shader_)
    {}

    Object& operator= (Object const& obj){
        if(this == &obj)
            return (*this);
        shader_ = obj.shader_;
        return (*this);
    }

    Material* getShader(){
        return shader_;
    }
    
    Vect3 virtual sample(){
        return Vect3();
    }
    
    Normal virtual getNormal(Vect3 const& point){
        return Normal();
    }
    
    double virtual pdf(){
        return 0;
    }
    
    void setShadowCast(bool b){
        shadow_cast = b;
    }
    
    virtual Box caluclateBoundingBox() = 0;
    virtual bool hit(Ray const& ray, Point3& intersection, double& tmin,Normal& normal) = 0;

public:
    bool shadow_cast = true;
    Material* shader_;
};

#endif /* Object_h */
