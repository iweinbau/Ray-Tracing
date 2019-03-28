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
    Object():
    position(Point3())
    {}

    Object(Point3 position):
    position(position)
    {}

    Object(Point3 position,Material* material):
    position(position),
    shader_(material)
    {}

    Object(Material* material):
    position(),
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

    Material* getShader(){
        return shader_;
    }

    virtual Box caluclateBoundingBox() = 0;
    virtual bool hit(Ray const& ray, Point3& intersection, double& tmin,Normal& normal) = 0;

public:
    Material* shader_;
    Point3 position;

};

#endif /* Object_h */
