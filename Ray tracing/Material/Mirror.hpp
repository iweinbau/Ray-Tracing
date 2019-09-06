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
#include "../Utils/GlobalTracer.hpp"
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

    Mirror(Lambertian ambient, Lambertian* diffuse, Glossy* specular,Specular* reflection):
    Phong(ambient,diffuse,specular),
    reflection(reflection)
    {}

    ~Mirror()
    {
        delete reflection;
    }


    Mirror& operator= (Mirror const& r)
    {
        if(this == &r)
            return (*this);

        Phong::operator=(r);
        specular = r.specular;
        return (*this);
    }

    Vect3 direct_shade(Hitinfo& hitinfo,World& world,int depth){
        Vect3 color = Phong::direct_shade(hitinfo,world,depth);
        
        Vect3 wo = hitinfo.direction.neg();
        Vect3 wi = reflection->sample_f(this, hitinfo, wo);
        double pdf = reflection->pdf(this, hitinfo, wi, wo);
        Vect3 reflective = reflection->eval(this,hitinfo,wi, wo);
        
        Ray reflectionRay = Ray(hitinfo.point + Vect3(hitinfo.normal) * kEpsilon, wi);
        color = color + (tr.trace(reflectionRay,world,depth+1)*reflective/pdf);
        return color;
    }
    
    Vect3 indirect_shade(Hitinfo& hitinfo,World& world,int depth){
        Vect3 wo = hitinfo.direction.neg();
        Vect3 wi = reflection->sample_f(this, hitinfo, wo);
        double pdf = reflection->pdf(this, hitinfo, wi, wo);
        Vect3 fs = reflection->eval(this,hitinfo, wi, wo);
        
        //Create new ray
        Ray r(hitinfo.point+ wi * kEpsilon,wi);
        Vect3 tracedColor;
        return (fs * tracedColor * hitinfo.normal.dot(wi)/pdf);
    }
    
    tracer tr;
    GlobalTracer gltr;

private:
    Specular* reflection;
};
#endif /* Mirror_h */
