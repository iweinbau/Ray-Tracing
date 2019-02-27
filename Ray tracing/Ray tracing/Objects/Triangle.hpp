//
//  Triangle.hpp
//  Ray Tracer
//
//  Created by Iwein Bau on 23/02/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#ifndef Triangle_h
#define Triangle_h

#include "Object.hpp"
#include "../Utils/Vect3.hpp"
#include "../Utils/ray.hpp"


class Triangle: public Object{
public:
    Triangle();
    Triangle(Vect3 v0,Vect3 v1, Vect3 v2,Material* material);
    ~Triangle();
    bool hit(Ray const& ray, Vect3& intersection, double& tmin);
    Vect3 getNormalAtPoint(Vect3 point);
private:
    Vect3 _v0,_v1,_v2;
    Vect3 _normal;
};

#endif /* Triangle_h */
