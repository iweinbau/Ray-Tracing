//
//  TriangleWorld.cpp
//  raytracer
//
//  Created by Iwein Bau on 17/03/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#include <stdio.h>

#include "./TriangleWorld.hpp"
#include "../Objects/Triangle.hpp"
#include "../Material/Phong.hpp"

void TriangleWorld::buildWorld(){
    //PointLight light(Vect3(1, 1,1), Vect3(5,5, -5),500);
    Light* light = new Light(Vect3(0.8, 0.8,0.8), Vect3(0,0, 5),3);
    
    add_Light(light);
    
    Phong* phong = new Phong(
                              Lambertian(1,Vect3(0.0,0.3,0)),
                              Lambertian(0.6,Vect3(0,1,0)),
                              Specular(0.2,5,Vect3(1,1,1)));
    
    //    Triangle(Vect3 v0,Vect3 v1, Vect3 v2,Material* material);
    // Triangle vertices are defined counter clock wise.
    Triangle* tri = new Triangle(Vect3(0, 2, 3), Vect3(-2, 0, 3),Vect3(2, 0, 3), phong);
    
    add_object(tri);
    
}
