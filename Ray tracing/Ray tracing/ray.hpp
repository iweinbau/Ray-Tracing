//
//  ray.hpp
//  Ray-tracer
//
//  Created by Iwein Bau on 16/12/2018.
//  Copyright © 2018 Iwein Bau. All rights reserved.
//

#ifndef ray_h
#define ray_h

class Ray {
public:
    Ray(Vect3 origin, Vect3 direction):origin_(origin), direction_(direction)
    {}
    
    Ray(Ray const& ray):origin_(ray.origin_),direction_(ray.direction_)
    {}
    
    Ray& operator= (Ray const& ray)
    {
        origin_ = ray.origin_;
        direction_ = ray.direction_;
        return *this;
    }
    
    ~Ray()
    {}
    
    //the origin point of the ray.
    Vect3 origin_;
    //the direction the ray is going.
    Vect3 direction_;
};

#endif /* ray_h */
