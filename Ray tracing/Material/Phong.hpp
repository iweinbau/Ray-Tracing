//
//  Phong.hpp
//  Ray-tracer
//
//  Created by Iwein Bau on 17/12/2018.
//  Copyright © 2018 Iwein Bau. All rights reserved.
//

#ifndef Phong_h
#define Phong_h

#include "Material.hpp"

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

    Lambertian* diffuse;
    Lambertian ambient;
    Glossy* specular;

};

#endif /* Phong_h */
