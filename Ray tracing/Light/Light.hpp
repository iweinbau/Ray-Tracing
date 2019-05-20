//
//  Light.hpp
//  Ray-tracer
//
//  Created by Iwein Bau on 17/12/2018.
//  Copyright © 2018 Iwein Bau. All rights reserved.
//

#ifndef Light_h
#define Light_h

#include "../Utils/Vect3.hpp"

class Hitinfo;
class World;

class Ray;
class Light {
public:
    Light(){}
    
    Light(Vect3 color,double i):
    color_(color),
    i_(i)
    {}

    Light(Light const& l):
    color_(l.color_),
    i_(l.i_)
    {}

    Light& operator= (Light const& l){
        if(this == &l)
            return (*this);

        color_ = l.color_;
        i_ = l.i_;
        return (*this);
    }

    Vect3 virtual getDirection(Hitinfo& hitinfo) = 0;

    Vect3 virtual getIntensity(Hitinfo& hitinfo,World& world) = 0;

    bool virtual shadow_hit(Ray const& ray,World& world) = 0;

protected:
    Vect3 color_;
    double i_;
};

#endif /* Light_h */
