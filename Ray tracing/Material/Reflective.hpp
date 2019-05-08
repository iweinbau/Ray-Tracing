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

    Reflective(Lambertian ambient, Lambertian* diffuse, Specular* specular,Glossy glossy):
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

    Vect3 shade(Hitinfo const& hitinfo,World const& world,int depth){
        Vect3 color = Phong::shade(hitinfo,world,depth);
        Vect3 reflection;
        double pdf;
        Vect3 reflectance = glossy.sample_(hitinfo,reflection,pdf);
        Ray reflectionRay = Ray(hitinfo.point + Vect3(hitinfo.normal)*kEpsilon, reflection);
        color = color + (tr.trace(reflectionRay,world,depth-1)*reflectance * std::max(0.0,hitinfo.normal.dot(reflection))/pdf);
        return color;
    }
    tracer tr;

private:
    Glossy glossy;
};
#endif /* Reflective_h */
