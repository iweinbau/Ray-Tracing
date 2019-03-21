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

//Destructor
Camera::~Camera(){};

//Constructor
Camera::Camera(){};
Camera::Camera(Vect3 lookfrom, Vect3 lookat, double fovy):
eye_(lookfrom),
lookat_(lookat),
fovy_(fovy),
aspect_(double(width)/double(height)),
direction_((lookat_ - lookfrom).normalize()),
up_(Vect3(0,1,0)){ // fov is top to bottom in degrees
    
    //degree to radian convertion.
    double tetha = (fovy_ * PI) / 180;
    double view_width = tan(tetha / 2) * distance_;
    double view_height = view_width / aspect_;
    
    horizontal_ = view_width * 2;
    vertical_ = view_height * 2;
    
    
    Vect3 center = eye_ + ( direction_ * distance_);
    
    u = direction_.neg();
    n = (up_.cross(u)).normalize();
    v = u.cross(n);
    
    upper_corner_ = center + (n.neg() * view_width) + (v * view_height);
    
}

Ray Camera::constructRay(int i, int j) {
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(0.0, 1.0);
    
    //From raytracing from the ground up.
    double x = dis(gen);
    double y = dis(gen);
    //calculate the ray.
    return Ray(eye_,(upper_corner_ + (n * (j+x) * (horizontal_/double(width))) + (v.neg() * (i+y) * (vertical_/double(height)))) - eye_);
}
