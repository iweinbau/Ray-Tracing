//
//  SmoothTriangle.cpp
//  raytracer
//
//  Created by Iwein Bau on 27/04/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#include "SmoothTriangle.hpp"

SmoothTriangle::SmoothTriangle():Triangle(){}

SmoothTriangle::SmoothTriangle(SmoothTriangle const& tri):
Triangle(tri),
n0(tri.n0),n1(tri.n1),n2(tri.n2){}

SmoothTriangle::SmoothTriangle(Point3 v0,Point3 v1, Point3 v2,Normal n0,Normal n1,Normal n2,Material* material):Triangle(v0,v1,v2,material),n0(n0),n1(n1),n2(n2){}
SmoothTriangle::SmoothTriangle(Point3 v0,Point3 v1, Point3 v2,Normal n0,Normal n1,Normal n2):Triangle(v0,v1,v2),n0(n0),n1(n1),n2(n2){}

Normal SmoothTriangle::calculate_normal(double gamma, double beta){
    return (Normal((1 - beta - gamma) * n0 + beta * n1 + gamma * n2)).normalize();
}
