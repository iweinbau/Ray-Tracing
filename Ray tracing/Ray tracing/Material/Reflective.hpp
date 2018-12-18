//
//  Reflective.hpp
//  Ray-tracer
//
//  Created by Iwein Bau on 17/12/2018.
//  Copyright © 2018 Iwein Bau. All rights reserved.
//

#ifndef Reflective_h
#define Reflective_h

#include "tracer.hpp"

class Reflective:public Phong{
public:
    Reflective():Phong()
    {}
    
    Reflective(Reflective const& refl):
    Phong(refl.ambient,refl.diffuse,refl.specular),
    reflective(refl.reflective)
    {}
    
    Reflective(Lambertian ambient, Lambertian diffuse, Specular specular,double reflective):
    Phong(ambient,diffuse,specular),
    reflective(reflective)
    {}
    
    ~Reflective()
    {}
    
    
    Reflective& operator= (Reflective const& r)
    {
        if(this == &r)
            return (*this);
        
        Reflective::operator=(r);
        reflective = r.reflective;
        return (*this);
    }
    
    Vect3 shade(Hitinfo const& hitinfo,std::list<Object*> objects,std::list<Light> lights,int depth){
        Vect3 reflection = hitinfo.direction - ( hitinfo.normal * 2 * hitinfo.direction.dot(hitinfo.normal));
        Ray reflectionRay = Ray(hitinfo.point + hitinfo.normal, reflection);
        Vect3 color = tr.trace(reflectionRay, objects, lights,depth-1) * reflective;
        return color * Phong::shade(hitinfo, objects, lights,depth);
    }
    tracer tr;
    
private:
    int depth = 2;
    double reflective;
};
#endif /* Reflective_h */
