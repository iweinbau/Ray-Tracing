//
//  tracer.hpp
//  Ray-tracer
//
//  Created by Iwein Bau on 17/12/2018.
//  Copyright © 2018 Iwein Bau. All rights reserved.
//

#ifndef tracer_h
#define tracer_h

#include "../Material/Material.hpp"
#include "../Builder/World.hpp"

#include "ray.hpp"
#include "../Objects/Object.hpp"

class tracer{
public:
    tracer()
    {}
    ~tracer()
    {}
    
    Vect3 trace(Ray const& ray,World& world,int depth) {
        
        if(depth > MAX_BOUNCE){
            return Vect3();
        }

        Vect3 color = Vect3(); //set initial color to background.

        double t;
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
            return closest->shader_->direct_shade(hitinfo,world,depth);
        }else{
            //no hit environment color.
            color = color + Vect3(1);
        }
        return color;
    }
};

#endif /* tracer_h */
