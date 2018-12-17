//
//  tracer.hpp
//  Ray-tracer
//
//  Created by Iwein Bau on 17/12/2018.
//  Copyright © 2018 Iwein Bau. All rights reserved.
//

#ifndef tracer_h
#define tracer_h

class tracer{
public:
    tracer()
    {}
    ~tracer()
    {}
    
    Vect3 trace(Ray ray, std::list<Object*> objects, std::list<Light> lights, int depth) {

        Vect3 color = Vect3(); //set initial color to background.

        double tmin = INFINITY;
        double t;
        Hitinfo hitinfo;
        hitinfo.direction = ray.direction_;
        
        Object* closest = nullptr;
        Vect3 intersection;
        
        bool hit = false;
        for(Object* obj : objects){
            if (obj->hit(ray, intersection, t)) {
                if (t < tmin) {
                    //we found a closer object.
                    hitinfo.point = intersection;
                    hitinfo.normal = obj->getNormalAtPoint(intersection);
                    closest = obj;
                    tmin = t;
                    hit = true;
                }
            }
        }
        
        if (hit) {
            return closest->shader_->shade(hitinfo, objects, lights,depth);
        }
        return color;
    }
};

#endif /* tracer_h */
