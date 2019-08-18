//
//  Camera.hpp
//  raytracer
//
//  Created by Iwein Bau on 25/02/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include "Vect3.hpp"
#include "ray.hpp"
#include "../Sampler/Sampler.hpp"

//Class that stores information about the camara.
//In create camera rays from it pointing in the world based on the properties.
class Camera {
public:
    //resolution in pixels.
    static const int width = 800, height = 800;
    Camera(Point3 lookfrom, Vect3 lookat, double fovy);
    Camera();
    ~Camera();
    Camera(Camera const& c):
    eye_(c.eye_),
    up_(c.up_),
    lookat_(c.lookat_),
    direction_(c.direction_),
    fovy_(c.fovy_),
    xAxis(c.xAxis),
    yAxis(c.yAxis),
    zAxis(c.zAxis),
    tanFovX(c.tanFovX),
    tanFovY(c.tanFovY)
    {}
    
    virtual Ray constructRay(int i, int j);

    Camera& operator= (Camera const& c)
    {
        eye_ = c.eye_;
        up_ = c.up_;
        lookat_ = c.lookat_;
        direction_ = c.direction_;
        tanFovX = c.tanFovX;
        tanFovY = c.tanFovY;
        fovy_ = c.fovy_;
        xAxis = c.xAxis;
        yAxis = c.yAxis;
        zAxis = c.zAxis;
        return *this;
    }
protected:
    const double distance_ = 1;
    //the position of the camera;
    Point3 eye_;
    Vect3 up_;
    Vect3 lookat_;
    Vect3 direction_;
    double fovy_;
    double tanFovX;
    double tanFovY;
    //unit vectors of the camera axis.
    Vect3 xAxis, yAxis, zAxis;
    
    Sampler sampler;
};

#endif /* Camera_hpp */
