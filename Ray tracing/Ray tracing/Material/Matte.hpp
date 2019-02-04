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
    
    virtual Vect3 shade(Hitinfo const& hitinfo,std::vector<Object*> const& objects,std::vector<Light*> const& lights,int depth){
        
        //********** AMBIENT COLOR ********** \\
        //set color to ambient light.
        Vect3 color = ambient.color();
        
        for(Light* l : lights){
            Vect3 lightDir = (l->getPosition() - hitinfo.point).normalize();
            
            //********* CAST SHADOW RAY ********** \\
            //cast shadow ray to check if the object is in shadow.
            Ray shadowray(hitinfo.point + hitinfo.normal * 0.0001,lightDir);
            
            bool hit = false;
            double t;
            double maxt = (l->getPosition() - hitinfo.point).length();
            Vect3 tmp;
            for(Object* obj : objects){
                if (obj->hit(shadowray,tmp, t)) {
                    if(t < maxt){
                        hit = true;
                        break;
                    }
                }
            }
            if(!hit){
                Vect3 df = diffuse.sample(hitinfo,lightDir) * l->getIntensity(hitinfo);
                color = color + df;
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
