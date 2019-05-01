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
    
    void add_object(Object* object){}
    virtual Box caluclateBoundingBox() = 0;
    virtual bool hit(Ray const& ray, Point3& intersection, double& tmin,Normal& normal) = 0;

public:
    Material* shader_;
};

#endif /* Object_h */
