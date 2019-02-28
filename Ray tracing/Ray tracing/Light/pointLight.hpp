//
//  pointLight.hpp
//  Ray-tracer
//
//  Created by Iwein Bau on 18/12/2018.
//  Copyright © 2018 Iwein Bau. All rights reserved.
//

#ifndef pointLight_h
#define pointLight_h

#include "Light.hpp"
#include "../Utils/Hitinfo.hpp"
#define PI 3.14159265


class PointLight : public Light{
public:
    PointLight(Vect3 color, Vect3 position,double i):
    Light(color,position,i)
    {}
    
    PointLight(PointLight const& l):
    Light(l)
    {}
    
    PointLight& operator= (PointLight const& l){
        if(this == &l)
            return (*this);
        
        Light::operator=(l);
        return (*this);
    }
    
    Vect3 virtual getIntensity(Hitinfo const& hitinfo){
        return (color_ * i_) / (hitinfo.d * hitinfo.d);
    }
};
#endif /* pointLight_h */
