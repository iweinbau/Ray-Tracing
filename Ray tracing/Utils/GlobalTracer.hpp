//
//  GlobalTracer.h
//  Ray GlobalTracer
//
//  Created by Iwein Bau on 06/06/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#ifndef GlobalTracer_h
#define GlobalTracer_h
#include "../Material/Material.hpp"
#include "../Builder/World.hpp"

#include "ray.hpp"
#include "../Objects/Object.hpp"

class GlobalTracer{
public:
    GlobalTracer()
    {}
    ~GlobalTracer()
    {}
    
    Vect3 trace(Ray const& ray,World& world,int depth) {
        
        if(depth > MAX_BOUNCE){
            return Vect3();
        }
        
        Vect3 color = Vect3(); //set initial color to background.
        
        double t = INFINITY;
        Hitinfo hitinfo;
        hitinfo.direction = ray.direction_;
        hitinfo.d = INFINITY;
        
        Object* closest = nullptr;
        Point3 intersection;
        Normal normal;
        
        bool hit = false;
        
        for(Object* obj : world.objects){
            if (obj->hit(ray, intersection, t, normal)) {
                if (t < hitinfo.d) {
                    //we found a closer object.
                    hitinfo.point = intersection;
                    hitinfo.normal = normal;
                    hitinfo.d = t;
                    closest = obj;
                    hit = true;
                }
            }
        }
        
        if (hit) {
            color = color + closest->shader_->indirect_shade(hitinfo,world,depth);
            return color;
        }else{
            //no hit environment color.
            color = color + Vect3(1);
        }
        return color;
    }
};

#endif /* GlobalGlobalTracer_h */
