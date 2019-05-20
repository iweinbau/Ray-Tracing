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
#include "../Utils/Normal.hpp"



class Triangle: public Object{
public:
    Triangle();
    Triangle(Point3 v0,Point3 v1, Point3 v2,Material* material);
    Triangle(Point3 v0,Point3 v1, Point3 v2);
    Normal virtual calculate_normal(double gamma, double beta);
    Box caluclateBoundingBox();
    ~Triangle();
    bool hit(Ray const& ray, Point3& intersection, double& tmin,Normal& normal);
protected:
    Point3 _v0,_v1,_v2;
    Normal _normal;
};

#endif /* Triangle_h */
