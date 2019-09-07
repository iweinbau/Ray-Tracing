//
//  Reflective.hpp
//  Ray-tracer
//
//  Created by Iwein Bau on 17/12/2018.
//  Copyright © 2018 Iwein Bau. All rights reserved.
//

#ifndef Reflective_h
#define Reflective_h

#include "../Utils/tracer.hpp"
#include "../Utils/GlobalTracer.hpp"

#include "../BRDF/Glossy.hpp"
#include "../Material/Phong.hpp"

#include "../Builder/World.hpp"

class Reflective:public Phong{
public:
    Reflective():Phong()
    {}

    Reflective(Reflective const& refl):
    Phong(refl.ambient,refl.diffuse,refl.specular)
    {
        if(refl.glossy){
            glossy = refl.glossy->clone();
        }else {
            glossy = NULL;
        }
    }

    Reflective(Lambertian ambient, Lambertian* diffuse, Glossy* specular,Glossy* glossy):
    Phong(ambient,diffuse,specular),
    glossy(glossy)
    {}

    ~Reflective()
    {
        delete glossy;
        glossy = NULL;
    }
    
    Material* clone() {
        return new Reflective(*this);
    }


    Reflective& operator= (Reflective const& r)
    {
        if(this == &r)
            return (*this);

        Reflective::operator=(r);
        
        if(glossy){
            delete glossy;
            glossy = NULL;
        }
        if(r.glossy){
            glossy = r.glossy->clone();
        }
        return (*this);
    }

    Vect3 direct_shade(Hitinfo& hitinfo,World& world,int depth){
        Vect3 color =Phong::direct_shade(hitinfo,world,depth);
        Vect3 wo = hitinfo.direction.neg();
        Vect3 wi = glossy->sample_f(this, hitinfo,wo);
        double pdf = glossy->pdf(this, hitinfo,wi, wo);
        Vect3 reflectance = glossy->eval(this,hitinfo,wi,wo);
        Ray reflectionRay = Ray(hitinfo.point + Vect3(hitinfo.normal)*kEpsilon, wi);
        
        color = color + (tr.trace(reflectionRay,world,depth+1)*reflectance * std::max(0.0,hitinfo.normal.dot(wi))/pdf);
        return color;
    }
    
    Vect3 indirect_shade(Hitinfo& hitinfo,World& world,int depth){
        Vect3 wo = hitinfo.direction.neg();
        Vect3 wi = glossy->sample_f(this, hitinfo, wo);
        double pdf = glossy->pdf(this, hitinfo, wi, wo);
        Vect3 fs = glossy->eval(this,hitinfo, wi, wo);
        //Create new ray
        Ray r(hitinfo.point+ wi * kEpsilon,wi);
        Vect3 tracedColor = gltr.trace(r, world, depth+1);
        
        return (fs * tracedColor * hitinfo.normal.dot(wi)/pdf);
    }
    
    
    GlobalTracer gltr;
    tracer tr;

private:
    Glossy* glossy;
};
#endif /* Reflective_h */
