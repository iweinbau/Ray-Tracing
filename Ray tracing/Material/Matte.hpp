//
//  Matte.hpp
//  Ray-tracer
//
//  Created by Iwein Bau on 17/12/2018.
//  Copyright © 2018 Iwein Bau. All rights reserved.
//

#ifndef Matte_h
#define Matte_h

#include "Material.hpp"
#include "../Utils/GlobalTracer.hpp"

class Matte: public Material{
public:
    Matte():Material()
    {}

    Matte(Lambertian ambient, Lambertian* diffuse):
    Material(),
    ambient(ambient),
    diffuse(diffuse)
    {}

    Matte(Matte const& matte):
    Material(),
    diffuse(matte.diffuse),
    ambient(matte.ambient)
    {}

    ~Matte()
    {}

    virtual Vect3 direct_shade(Hitinfo& hitinfo,World& world,int depth){

        //********** AMBIENT COLOR ********** \\
        //set color to ambient light.
        Vect3 color = ambient.color() * world.ambientLight.getIntensity(hitinfo, world);

        for(Light* l : world.lights){
            Vect3 lightDir = l->getDirection(hitinfo);
            //********* CAST SHADOW RAY ********** \\
            //cast shadow ray to check if the object is in shadow.
            Ray shadowray(hitinfo.point + Vect3(hitinfo.normal) * kEpsilon,lightDir);
            
            if(!l->shadow_hit(shadowray,world)){
                double ndotLightDir = hitinfo.normal.dot(lightDir);
                Vect3 tmp;
                if(ndotLightDir > 0){
                    Vect3 df = diffuse->f(hitinfo,lightDir,tmp) * ndotLightDir * l->getIntensity(hitinfo,world);
                    color = color + df;
                }
            }
        }
        return color;
    }
    
    Vect3 indirect_shade(Hitinfo& hitinfo,World& world,int depth){
        
        Vect3 color;
        
        if(depth == 0){
            color = direct_shade(hitinfo, world, depth);
        }
        
        Vect3 wi;
        Vect3 wo = hitinfo.direction.neg();
        double pdf;
        Vect3 f = diffuse->sample_f(hitinfo, wi, wo, pdf);
        //Create new ray
        
        Ray r(hitinfo.point+ wi * kEpsilon,wi);
        Vect3 tracedColor = gltr.trace(r, world, depth+1);
        
        return color + (f * tracedColor * hitinfo.normal.dot(wi)/pdf);
    }

    Matte& operator= (Matte const& matte)
    {
        if(this == &matte)
            return (*this);

        Material::operator=(matte);

        diffuse = matte.diffuse;
        ambient = matte.ambient;

        return (*this);
    }
    
    GlobalTracer gltr;

    Lambertian* diffuse;
    Lambertian ambient;
    
    
};

#endif /* Matte_h */
