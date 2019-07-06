//
//  Rectangle.hpp
//  raytracer
//
//  Created by Iwein Bau on 01/05/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#ifndef Rectangle_hpp
#define Rectangle_hpp

#include "Object.hpp"
#include "../Sampler/Sampler.hpp"

class Rectangle: public Object {
public:
    Rectangle();
    Rectangle(Point3 p0,Vect3 v1, Vect3 v2);
    Rectangle(Point3 p0,Vect3 v1, Vect3 v2,Material* mat);
    ~Rectangle();

    
    Box caluclateBoundingBox();
    bool hit(Ray const& ray, Point3& intersection, double& tmin,Normal& normal);
    Vect3 sample();
    Vect3 getNormal(Vect3 point);
    double pdf();
private:
    Sampler sampler;
    Point3 p0;
    Vect3 a;
    Vect3 b;
    Normal n;
    
};
#endif /* Rectangle_hpp */
