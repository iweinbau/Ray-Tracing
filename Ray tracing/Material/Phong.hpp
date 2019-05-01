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
#include "../BRDF/Specular.hpp"

#include "../Light/Light.hpp"

class Phong:public Material{
public:
    Phong():Material()
    {}

    Phong(Lambertian ambient, Lambertian diffuse, Specular specular):
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

    virtual Vect3 shade(Hitinfo const& hitinfo,World const& world,int depth){

        //********** AMBIENT COLOR ********** \\
        //set color to ambient light.
        Vect3 color = ambient.color();

        for(Light* l : world.lights){
            Vect3 lightDir = l->getDirection(hitinfo);
            //********* CAST SHADOW RAY ********** \\
            //cast shadow ray to check if the object is in shadow.
            Ray shadowray(hitinfo.point + Vect3(hitinfo.normal) * 0.0001,lightDir);

            if(!l->shadow_hit(shadowray,world)){
                Vect3 specularV;
                Vect3 sp = specular.sample(hitinfo,lightDir,specularV);
                Vect3 df = diffuse.sample(hitinfo,lightDir);
                Vect3 li = l->getIntensity(hitinfo);
                color = color + (df + sp) * std::max(0.0,hitinfo.normal.dot(lightDir)) * li;
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

    Lambertian diffuse;
    Lambertian ambient;
    Specular specular;

};

#endif /* Phong_h */
