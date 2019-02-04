//
//  Light.hpp
//  Ray-tracer
//
//  Created by Iwein Bau on 17/12/2018.
//  Copyright © 2018 Iwein Bau. All rights reserved.
//

#ifndef Light_h
#define Light_h

#include "../vector3f.hpp"

class Light {
public:
    Light(Vect3 color,Vect3 position,double i):
    color_(color),
    position_(position),
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
    
    Vect3 getPosition() {
        return position_;
    }
    
    Vect3 virtual getIntensity(Hitinfo const& hitinfo){
        return color_ * i_;
    };
    
private:
    Vect3 position_;
protected:
    Vect3 color_;
    double i_;
};

#endif /* Light_h */
