//
//  Mirror.hpp
//  Ray-tracer
//
//  Created by Iwein Bau on 03/02/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#ifndef Mirror_h
#define Mirror_h

#include "../tracer.hpp"
#include "../BRDF/Specular.hpp"
#include "Phong.hpp"


class Mirror:public Phong{
public:
    Mirror():Phong()
    {}

    Mirror(Mirror const& mirror):
    Phong(mirror.ambient,mirror.diffuse,mirror.specular),
    specular(mirror.specular)
    {}

    Mirror(Lambertian ambient, Lambertian* diffuse, Specular* specular,Specular* reflection):
    Phong(ambient,diffuse,specular),
    specular(reflection)
    {}

    ~Mirror()
    {}


    Mirror& operator= (Mirror const& r)
    {
        if(this == &r)
            return (*this);

        Phong::operator=(r);
        specular = r.specular;
        return (*this);
    }

    Vect3 shade(Hitinfo const& hitinfo,World const& world,int depth){
        Vect3 color = Phong::shade(hitinfo,world,depth);
        Vect3 reflection;
        Vect3 reflective = specular->sample(hitinfo, hitinfo.direction.neg(), reflection);
        Ray reflectionRay = Ray(hitinfo.point + Vect3(hitinfo.normal) * kEpsilon, reflection);
        color = color + (tr.trace(reflectionRay,world,depth-1)*reflective);
        return color;
    }
    tracer tr;

private:
    Specular* specular;
};
#endif /* Mirror_h */
