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
#include "../Material/Phong.hpp"

#include "../Builder/World.hpp"

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

    Vect3 shade(Hitinfo const& hitinfo,World world,int depth){
        Vect3 color = Phong::shade(hitinfo,world,depth);
        for (int i=0; i<NUM_SAMPLES; i++) {
            Vect3 reflection;
            Vect3 reflectance = glossy.sample_(hitinfo,reflection);
            Ray reflectionRay = Ray(hitinfo.point + hitinfo.normal, reflection);
            color = color + (tr.trace(reflectionRay,world,depth-1)*reflectance);
        }
        return color/NUM_SAMPLES;
    }
    tracer tr;

private:
    Glossy glossy;
};
#endif /* Reflective_h */
