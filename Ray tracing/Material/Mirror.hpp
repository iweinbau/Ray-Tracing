//
//  Mirror.hpp
//  Ray-tracer
//
//  Created by Iwein Bau on 03/02/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#ifndef Mirror_h
#define Mirror_h

#include "../Utils/tracer.hpp"
#include "../BRDF/Specular.hpp"
#include "../BRDF/Glossy.hpp"
#include "Phong.hpp"


class Mirror:public Phong{
public:
    Mirror():Phong()
    {}

    Mirror(Mirror const& mirror):
    Phong(mirror.ambient,mirror.diffuse,mirror.specular),
    reflection(mirror.reflection)
    {}

    Mirror(Lambertian ambient, Lambertian* diffuse, Specular* specular,Glossy* reflection):
    Phong(ambient,diffuse,specular),
    reflection(reflection)
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

    Vect3 shade(Hitinfo& hitinfo,World& world,int depth){
        Vect3 color = Phong::shade(hitinfo,world,depth);
        Vect3 r;
        Vect3 reflective = reflection->sample(hitinfo, hitinfo.direction.neg(), r);
        Ray reflectionRay = Ray(hitinfo.point + Vect3(hitinfo.normal) * kEpsilon, r);
        color = color + (tr.trace(reflectionRay,world,depth-1)*reflective * std::max(0.0,hitinfo.normal.dot(r)));
        return color;
    }
    tracer tr;

private:
    Glossy* reflection;
};
#endif /* Mirror_h */
