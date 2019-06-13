//
//  Phong.hpp
//  Ray-tracer
//
//  Created by Iwein Bau on 17/12/2018.
//  Copyright © 2018 Iwein Bau. All rights reserved.
//

#ifndef Phong_h
#define Phong_h
#include <math.h>


#include "Material.hpp"

#include "../Utils/GlobalTracer.hpp"
#include "../Objects/sphere.hpp"
#include "../BRDF/Lambertian.hpp"
#include "../BRDF/Glossy.hpp"

#include "../Light/Light.hpp"

class Phong:public Material{
public:
    Phong():Material()
    {}

    Phong(Lambertian ambient, Lambertian* diffuse, Glossy* specular):
    Material(),
    ambient(ambient),
    diffuse(diffuse),
    specular(specular)
    {}

    Phong(Phong const& phong):
    Material(),
    ambient(phong.ambient),
    diffuse(phong.diffuse),
    specular(phong.specular)
    {}

    ~Phong()
    {}

    virtual Vect3 direct_shade(Hitinfo& hitinfo,World& world,int depth){

        //********** AMBIENT COLOR ********** \\
        //set color to ambient light.
        Vect3 color = ambient.color() * world.ambientLight.getIntensity(hitinfo, world);
        Vect3 wo = hitinfo.direction.neg();
        
        for(Light* l : world.lights){
            Vect3 wi = l->getDirection(hitinfo);
            //********* CAST SHADOW RAY ********** \\
            //cast shadow ray to check if the object is in shadow.
            Ray shadowray(hitinfo.point + Vect3(hitinfo.normal) * 0.0001,wi);

            if(!l->shadow_hit(shadowray,world)){
                Vect3 sp = specular->f(hitinfo,wi,wo);
                Vect3 df = diffuse->f(hitinfo,wi,wo);
                Vect3 li = l->getIntensity(hitinfo,world);
                color = color + (df + sp) * hitinfo.normal.dot(wi) * li;
            }
        }
        return color;
    }
    
    Vect3 indirect_shade(Hitinfo& hitinfo,World& world,int depth){
        std::random_device rd;  //Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
        std::uniform_real_distribution<> dis(0.0, 1.0);
        
        double p = dis(gen);
        //first probability of diffuse.
        double q1 = 1/PI;
        double q2 = (specular->e +2)/(2 * PI);
        
        //second probability of specular.
        //calculate diffuse first.
        //calculate specular second.
        Vect3 wo = hitinfo.direction.neg();
        Vect3 wi;

        if(p <  diffuse->kd){
            //sample in diffuse lobe.
             wi = diffuse->sample_f(this, hitinfo, wo);
        }else if( diffuse->kd <= p && p < diffuse->kd + specular->ks){
            //sample specular lobe.
            wi = specular->sample_f(this, hitinfo, wo);
        }else{
            return Vect3();
        }
        double pdfd = diffuse->pdf(this, hitinfo, wi, wo);
        double pdfs = specular->pdf(this, hitinfo, wi, wo);
        Vect3 f = diffuse->eval(this,hitinfo, wi, wo);
        Vect3 fs = specular->eval(this, hitinfo, wi, wo);

        //Create new ray
        Ray r(hitinfo.point+ wi * kEpsilon,wi);
        Vect3 tracedColor = gltr.trace(r, world, depth+1);
        return (tracedColor * (f + q2*fs) * hitinfo.normal.dot(wi))/(pdfd + q2*pdfs);
    }

    Phong& operator= (Phong const& phong)
    {
        if(this == &phong)
            return (*this);

        Material::operator=(phong);

        diffuse = phong.diffuse;
        ambient = phong.ambient;
        specular = phong.specular;

        return (*this);
    }

    GlobalTracer gltr;
    Lambertian* diffuse;
    Lambertian ambient;
    Glossy* specular;

};

#endif /* Phong_h */
