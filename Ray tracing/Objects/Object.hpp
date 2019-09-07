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
#include "../Material/Material.hpp"


class Object{
public:
    Object(){}

    Object(Material* material):
    shader_(material)
    {}
    
    virtual ~Object(){
        if(shader_) {
            delete shader_;
            shader_ = NULL;
        }
    }
    
    virtual Object* clone() =0;

    Object(Object const& obj){
        if(obj.shader_){
            shader_ = obj.shader_->clone();
        }else {
            shader_ = NULL;
        }
    }

    Object& operator= (Object const& obj){
        if(this == &obj)
            return (*this);
        if(shader_){
            delete shader_;
            shader_ = NULL;
        }
        if(obj.shader_){
            shader_ = obj.shader_->clone();
        }
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
    Material* shader_ = NULL;
};

#endif /* Object_h */
