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

//Class that stores information about the camara.
//In create camera rays from it pointing in the world based on the properties.
class Camera {
public:
    //resolution in pixels.
    static const int width = 800, height = 800;
    static const int num_samples = 1;
    Camera(Vect3 lookfrom, Vect3 lookat, double fovy);
    Camera();
    ~Camera();
    Ray constructRay(int i, int j);
    Camera(Camera const& c):
    eye_(c.eye_),
    up_(c.up_),
    lookat_(c.lookat_),
    direction_(c.direction_),
    fovy_(c.fovy_),
    aspect_(c.aspect_),
    upper_corner_(c.upper_corner_),
    horizontal_(c.horizontal_),
    vertical_(c.vertical_),
    u(c.u),
    v(c.v),
    n(c.n)
    {}

    Camera& operator= (Camera const& c)
    {
        eye_ = c.eye_;
        up_ = c.up_;
        lookat_ = c.lookat_;
        direction_ = c.direction_;
        fovy_ = c.fovy_;
        aspect_ = c.aspect_;
        upper_corner_ = c.upper_corner_;
        horizontal_ = c.horizontal_;
        vertical_ = c.vertical_;
        u = c.u;
        v = c.v;
        n = c.n;
        return *this;
    }
private:
    const double distance_ = 1;
    //the position of the camera;
    Vect3 eye_;
    Vect3 up_;
    Vect3 lookat_;
    Vect3 direction_;
    double fovy_;
    double aspect_;
    Vect3 upper_corner_;
    //the horizontal vector/of the image view.
    double horizontal_;
    //the vertical vector of the image view.
    double vertical_;
    //unit vectors of the camera axis.
    Vect3 u, v, n;
};

#endif /* Camera_hpp */
