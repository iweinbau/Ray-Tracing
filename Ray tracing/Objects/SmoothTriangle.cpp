//
//  SmoothTriangle.cpp
//  raytracer
//
//  Created by Iwein Bau on 27/04/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#include "SmoothTriangle.hpp"

SmoothTriangle::SmoothTriangle():Triangle(){}
SmoothTriangle::SmoothTriangle(Point3 v0,Point3 v1, Point3 v2,Material* material):Triangle(v0,v1,v2,material){}
SmoothTriangle::SmoothTriangle(Point3 v0,Point3 v1, Point3 v2):Triangle(v0,v1,v2){}
Normal SmoothTriangle::calculate_normal(double gamma, double beta){
    return Normal((1 - beta - gamma) * _v0 + beta * _v1 + gamma * _v2);
}
