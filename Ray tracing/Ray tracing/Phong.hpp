//
//  Phong.hpp
//  Ray-tracer
//
//  Created by Iwein Bau on 17/12/2018.
//  Copyright © 2018 Iwein Bau. All rights reserved.
//

#ifndef Phong_h
#define Phong_h

#include <iostream>
#include "sphere.hpp"
#include "material.hpp"
#include "Lambertian.hpp"
#include "Specular.hpp"
#include "Hitinfo.hpp"
#include "Light.hpp"

class Phong{
public:
    Phong()
    {}
    
    Phong(Lambertian ambient, Lambertian diffuse, Specular specular):
    ambient(ambient),
    diffuse(diffuse),
    specular(specular)
    {}
    
    ~Phong()
    {}
    
    virtual Vect3 shade(Hitinfo const& hitinfo,std::list<Sphere> objects,std::list<Light> lights,int depth){
        
        //********** AMBIENT COLOR ********** \\
        //set color to ambient light.
        Vect3 color = ambient.color();
        
        for(Light l : lights){
            Vect3 lightDir = (l.getPosition() - hitinfo.point).normalize();
            
            //********* CAST SHADOW RAY ********** \\
            //cast shadow ray to check if the object is in shadow.
            Ray shadowray(hitinfo.point + hitinfo.normal * 0.0001,lightDir);
            
            bool hit = false;
            double t;
            double maxt = (l.getPosition() - hitinfo.point).length();
            Vect3 tmp;
            for(Sphere obj : objects){
                if (obj.hit(shadowray,tmp, t)) {
                    if(t < maxt){
                        hit = true;
                        break;
                    }
                }
            }
            if(!hit){
                Vect3 df = diffuse.sample(hitinfo,lightDir) * l.getDiffuse();
                Vect3 sp = specular.sample(hitinfo,lightDir) * l.getSpecular();
                color = color + df + sp;
            }
        }
        return color;
    }
    
    Phong& operator= (Phong const& phong)
    {
        if(this == &phong)
            return (*this);
        
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
