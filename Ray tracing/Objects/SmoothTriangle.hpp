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
    SmoothTriangle(Point3 v0,Point3 v1, Point3 v2,Material* material);
    SmoothTriangle(Point3 v0,Point3 v1, Point3 v2);
    Normal virtual calculate_normal(double gamma, double beta);
};

#endif /* SmoothTriangle_hpp */
