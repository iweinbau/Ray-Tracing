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

    virtual Vect3 shade(Hitinfo& hitinfo,World& world,int depth){

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
                    Vect3 df = diffuse->sample(hitinfo,lightDir,tmp) * ndotLightDir * l->getIntensity(hitinfo,world);
                    color = color + df;
                }
            }
        }
        return color;
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

    Lambertian* diffuse;
    Lambertian ambient;
};

#endif /* Matte_h */
