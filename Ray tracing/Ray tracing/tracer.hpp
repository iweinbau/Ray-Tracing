//
//  tracer.hpp
//  Ray-tracer
//
//  Created by Iwein Bau on 17/12/2018.
//  Copyright © 2018 Iwein Bau. All rights reserved.
//

#ifndef tracer_h
#define tracer_h

#include "./Material/Material.hpp"
#include "./Builder/World.hpp"

class tracer{
public:
    tracer()
    {}
    ~tracer()
    {}
    
    Vect3 trace(Ray const& ray,World const& world,int depth) {
        
        if(depth <= 0){
            return Vect3(1,1,1);
        }
        
        Vect3 color = Vect3(); //set initial color to background.

        double t;
        Hitinfo hitinfo;
        hitinfo.direction = ray.direction_;
        hitinfo.d = INFINITY;
        
        Object* closest = nullptr;
        Vect3 intersection;
        
        bool hit = false;
        
        for(Object* obj : world.objects){
            if (obj->hit(ray, intersection, t)) {
                if (t < hitinfo.d) {
                    //we found a closer object.
                    hitinfo.point = intersection;
                    hitinfo.normal = obj->getNormalAtPoint(intersection);
                    hitinfo.d = t;
                    closest = obj;
                    hit = true;
                }
            }
        }
        
        if (hit) {
            return closest->shader_->shade(hitinfo,world,depth);
        }
        return color;
    }
};

#endif /* tracer_h */
