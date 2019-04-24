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
    
    Matte(Lambertian ambient, Lambertian diffuse):
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
    
    virtual Vect3 shade(Hitinfo const& hitinfo,World world,int depth){
        
        //********** AMBIENT COLOR ********** \\
        //set color to ambient light.
        Vect3 color = ambient.color();
        
        for(Light* l : world.lights){
            Vect3 lightDir = (l->getPosition() - hitinfo.point).normalize();
            //********* CAST SHADOW RAY ********** \\
            //cast shadow ray to check if the object is in shadow.
            Ray shadowray(hitinfo.point + Vect3(hitinfo.normal) * kEpsilon,lightDir);
            bool hit = false;
            double t;
            double maxt = (l->getPosition() - hitinfo.point).length();
            Point3 intersection;
            Normal normal;
            for(Object* obj : world.objects){
                if (obj->hit(shadowray,intersection, t,normal)) {
                    if(t < maxt){
                        //we found a closer object.
                        hit = true;
                        break;
                    }
                }
            }
            if(!hit){
                Hitinfo lightHit;
                lightHit.d = maxt;
                double ndotLightDir = hitinfo.normal.dot(lightDir);
                if(ndotLightDir > 0){
                    Vect3 df = diffuse.sample(hitinfo,lightDir) * ndotLightDir * l->getIntensity(lightHit);
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
    
    Lambertian diffuse;
    Lambertian ambient;
};

#endif /* Matte_h */
