//
//  Reflective.hpp
//  Ray-tracer
//
//  Created by Iwein Bau on 17/12/2018.
//  Copyright © 2018 Iwein Bau. All rights reserved.
//

#ifndef Reflective_h
#define Reflective_h

#include "../tracer.hpp"
#include "../BRDF/Glossy.hpp"

class Reflective:public Phong{
public:
    Reflective():Phong()
    {}
    
    Reflective(Reflective const& refl):
    Phong(refl.ambient,refl.diffuse,refl.specular),
    glossy(refl.glossy)
    {}
    
    Reflective(Lambertian ambient, Lambertian diffuse, Specular specular,Glossy glossy):
    Phong(ambient,diffuse,specular),
    glossy(glossy)
    {}
    
    ~Reflective()
    {}
    
    
    Reflective& operator= (Reflective const& r)
    {
        if(this == &r)
            return (*this);
        
        Reflective::operator=(r);
        glossy = r.glossy;
        return (*this);
    }
    
    Vect3 shade(Hitinfo const& hitinfo,std::vector<Object*> const& objects,std::vector<Light*> const& lights,int depth){
        Vect3 color = Phong::shade(hitinfo, objects, lights,depth);
        for (int i=0; i<samples; i++) {
            Vect3 reflection;
            Vect3 reflectance = glossy.sample_(hitinfo,reflection);
            Ray reflectionRay = Ray(hitinfo.point + hitinfo.normal, reflection);
            color = color + (tr.trace(reflectionRay, objects, lights,depth-1)*reflectance);
        }
        return color/samples;
    }
    tracer tr;
    
private:
    static const int samples = 50;
    Glossy glossy;
};
#endif /* Reflective_h */
