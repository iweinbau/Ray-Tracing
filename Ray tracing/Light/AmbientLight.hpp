//
//  AmbientLight.hpp
//  raytracer
//
//  Created by Iwein Bau on 20/05/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#ifndef AmbientLight_hpp
#define AmbientLight_hpp

#include "Light.hpp"
#include "../Sampler/Sampler.hpp"

class AmbientLight : public Light{
public:
    AmbientLight():
    Light(),factor(0)
    {}
    
    AmbientLight(double factor,Vect3 color,double i):
    Light(color,i),factor(factor)
    {}
    
    AmbientLight(AmbientLight const& l):Light(l.color_,l.i_),factor(l.factor)
    {}
    
    AmbientLight& operator= (AmbientLight const& l){
        if(this == &l)
            return (*this);
        
        Light::operator=(l);
        factor = l.factor;
        
        return (*this);
    }
    
    Vect3 getDirection(Hitinfo& hitinfo);
    
    Vect3 getIntensity(Hitinfo& hitinfo,World& world);

    bool shadow_hit(Ray const& ray,World& world);
private:
    double factor;
    Sampler sampler;
};

#endif /* AmbientLight_hpp */
