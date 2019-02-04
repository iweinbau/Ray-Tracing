//
//  Mirror.hpp
//  Ray-tracer
//
//  Created by Iwein Bau on 03/02/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#ifndef Mirror_h
#define Mirror_h

#include "../tracer.hpp"
#include "../BRDF/Specular.hpp"

class Mirror:public Phong{
public:
    Mirror():Phong()
    {}
    
    Mirror(Mirror const& mirror):
    Phong(mirror.ambient,mirror.diffuse,mirror.specular),
    specular(mirror.specular)
    {}
    
    Mirror(Lambertian ambient, Lambertian diffuse, Specular specular,Specular reflection):
    Phong(ambient,diffuse,specular),
    specular(reflection)
    {}
    
    ~Mirror()
    {}
    
    
    Mirror& operator= (Mirror const& r)
    {
        if(this == &r)
            return (*this);
        
        Phong::operator=(r);
        specular = r.specular;
        return (*this);
    }
    
    Vect3 shade(Hitinfo const& hitinfo,std::vector<Object*> const& objects,std::vector<Light*> const& lights,int depth){
        Vect3 color = Phong::shade(hitinfo, objects, lights,depth);
        Vect3 reflection;
        specular.sample(hitinfo, hitinfo.direction.neg(), reflection);
        Ray reflectionRay = Ray(hitinfo.point + hitinfo.normal* 0.001, reflection);
        color = color + (tr.trace(reflectionRay, objects, lights,depth-1)*specular.color());
        return color;
    }
    tracer tr;
    
private:
    Specular specular;
};
#endif /* Mirror_h */
