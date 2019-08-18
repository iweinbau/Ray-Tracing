//
//  Camera.cpp
//  raytracer
//
//  Created by Iwein Bau on 25/02/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#include <random>

#include "Camera.hpp"
#include "Constants.hpp"
#include "Matrix.hpp"

//Destructor
Camera::~Camera(){};

//Constructor
Camera::Camera(){};
Camera::Camera(Point3 lookfrom, Vect3 lookat, double fovy):
eye_(lookfrom),
lookat_(lookat),
fovy_(fovy),
direction_((eye_ - lookat).normalize()),
up_(Vect3(0,1,0)){ // fov is top to bottom in degrees

    //degree to radian convertion.
    double tetha = (fovy_ * PI) / 180;
    tanFovX = tan(tetha / 2);
    tanFovY = tan((tetha / 2) *  double(height) / double (width));

    zAxis = direction_;
    xAxis = (up_.cross(zAxis)).normalize();
    yAxis = zAxis.cross(xAxis);

}

Ray Camera::constructRay(int i, int j) {
    double x = sampler.sample();
    double y = sampler.sample();
    
    Vect3 viewVector( (((i+x) / double(width)) * 2.0 - 1.0) * tanFovX, -(((j+y) / double(width)) * 2.0 - 1.0) * tanFovY, -1.0);
    
    Vect3 dir(viewVector.dot(Vect3(xAxis.x_, yAxis.x_, zAxis.x_)),
              viewVector.dot(Vect3(xAxis.y_, yAxis.y_, zAxis.y_)),
              viewVector.dot(Vect3(xAxis.z_, yAxis.z_, zAxis.z_)));
    
    //calculate the ray.
    return Ray(eye_,dir.normalize());
}
