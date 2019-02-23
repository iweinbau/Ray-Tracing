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
#include "../vector3f.hpp"
#include "../ray.hpp"

class Triangle: public Object{
public:
    Triangle();
    Triangle(Vect3 const& v0,Vect3 const& v1, Vect3 const& v2,Material* material);
    ~Triangle();
    bool hit(Ray& ray, Vect3& intersection, double& tmin);
    Vect3 getNormalAtPoint(Vect3 point);
private:
    Vect3 _v0,_v1,_v2;
    Vect3 _normal;
};

#endif /* Triangle_h */
