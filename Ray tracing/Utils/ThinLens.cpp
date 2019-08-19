//
//  ThinLens.cpp
//  Ray-tracing
//
//  Created by Iwein Bau on 17/08/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#include "ThinLens.hpp"
#include "../3D-Model-Parser/OBJ-Loader/Utils/Vect2.hpp"

ThinLens::ThinLens(Point3 lookfrom, Vect3 lookat, double fovy, double focal, double apertureSize):
    Camera(lookfrom,lookat,fovy),
    focalDistance(focal),
    apertureSize(apertureSize){}

ThinLens::ThinLens():Camera(){}

ThinLens::~ThinLens(){}

Ray ThinLens::constructRay(int i, int j){
    double x = sampler.sample();
    double y = sampler.sample();
        
    Vect3 pixelOnfocalPlane((((i + x) / double(width)) * 2.0 - 1.0) * tanFovX * (focalDistance/distance_),
                    -(((j + y) / double(width)) * 2.0 - 1.0) * tanFovY * (focalDistance/distance_),
                    -focalDistance);
    
    //point in eyeSpace
    Vect3 pointOnFocalPlane(pixelOnfocalPlane.dot(Vect3(xAxis.x_, yAxis.x_, zAxis.x_)),
                            pixelOnfocalPlane.dot(Vect3(xAxis.y_, yAxis.y_, zAxis.y_)),
                            pixelOnfocalPlane.dot(Vect3(xAxis.z_, yAxis.z_, zAxis.z_)));
    
    //point in worldSpace
    pointOnFocalPlane = eye_ + pointOnFocalPlane;
    
    Vect2 lensSample = sampler.samplePointOnUnitDisk() * apertureSize;
    Vect3 translatedEye = eye_ + xAxis * lensSample.x_ + yAxis * lensSample.y_;
    
    Vect3 dir = pointOnFocalPlane - translatedEye;
    
    //calculate the ray.
    return Ray(translatedEye,dir.normalize());
}

