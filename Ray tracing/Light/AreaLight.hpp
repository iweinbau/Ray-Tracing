//
//  AreaLight.hpp
//  raytracer
//
//  Created by Iwein Bau on 01/05/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#ifndef AreaLight_hpp
#define AreaLight_hpp

#include "Light.hpp"

class Object;

class AreaLight: public Light {
public:
    AreaLight(Object* object,Vect3 color,double i);
    
    AreaLight(AreaLight const& l);
    
    Vect3 getDirection(Hitinfo const& hitinfo);
    
    Vect3 getIntensity(Hitinfo const& hitinfo);
    
    bool shadow_hit(Ray const& ray,World const& world);
private:
    Object* obj;
    Vect3 direction;
    Vect3 normal;
    Vect3 samplePoint;
};
#endif /* AreaLight_hpp */
