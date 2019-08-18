//
//  ThinLens.cpp
//  Ray-tracing
//
//  Created by Iwein Bau on 17/08/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#include "ThinLens.hpp"

ThinLens::ThinLens(Point3 lookfrom, Vect3 lookat, double fovy, double lensRadius, double focal):
    Camera(lookfrom,lookat,fovy),
    lensRadius(lensRadius),
    focalDistance(focal){}

ThinLens::ThinLens():Camera(){}

ThinLens::~ThinLens(){}

Ray ThinLens::constructRay(int i, int j){
    double x = sampler.sample();
    double y = sampler.sample();
    
    Vect3 viewVector( (((i+x) / double(width)) * 2.0 - 1.0) * tanFovX, -(((j+y) / double(width)) * 2.0 - 1.0) * tanFovY, -1.0);
    
    Vect3 dir(viewVector.dot(Vect3(xAxis.x_, yAxis.x_, zAxis.x_)),
              viewVector.dot(Vect3(xAxis.y_, yAxis.y_, zAxis.y_)),
              viewVector.dot(Vect3(xAxis.z_, yAxis.z_, zAxis.z_)));
    
    //calculate the ray.
    return Ray(eye_,dir.normalize());
}

