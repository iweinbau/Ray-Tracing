//
//  SmoothTriangle.hpp
//  raytracer
//
//  Created by Iwein Bau on 27/04/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#ifndef SmoothTriangle_hpp
#define SmoothTriangle_hpp

#include "Triangle.hpp"

class SmoothTriangle : public Triangle{
public:
    SmoothTriangle();
    SmoothTriangle(Point3 v0,Point3 v1, Point3 v2,Normal n0,Normal n1,Normal n2,Material* material);
    SmoothTriangle(Point3 v0,Point3 v1, Point3 v2,Normal n0,Normal n1,Normal n2);
    Normal virtual calculate_normal(double gamma, double beta);
private:
    Normal n0;
    Normal n1;
    Normal n2;
};

#endif /* SmoothTriangle_hpp */
