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
#include "../Utils/Point3.hpp"
#include "../Utils/Normal.hpp"


class Object;
class Point3;

class AreaLight: public Light {
public:
    AreaLight(Object* object,Vect3 color,double i);
    
    AreaLight(AreaLight const& l);
    
    ~AreaLight();
    
    Vect3 getDirection(Hitinfo& hitinfo);
    
    Vect3 getIntensity(Hitinfo& hitinfo,World& world);
    
    bool shadow_hit(Ray const& ray,World& world);
private:
    Object* obj;
    Vect3 direction;
    Normal normal;
    Point3 samplePoint;
};
#endif /* AreaLight_hpp */
