//
//  World.cpp
//  raytracer
//
//  Created by Iwein Bau on 25/02/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//


#include "./World.hpp"

#include "../Material/Mirror.hpp"
#include "../Material/Phong.hpp"
#include "../Material/Reflective.hpp"
#include "../Material/Matte.hpp"

#include "../Objects/sphere.hpp"
#include "../Objects/Plane.hpp"


//Constructor
World::World(){}
World::~World(){}

void World::buildWorld(){
    //World setup
    
    //PointLight light(Vect3(1, 1,1), Vect3(5,5, -5),500);
    Light* light2 = new Light(Vect3(0.8, 0.8,0.8), Vect3(-5,0, 5),3);
    
    Reflective* phong = new Reflective(
                     Lambertian(0.25,Vect3(0.3,0.3,0.3)),
                     Lambertian(0.6,Vect3(0.4,0.4,0.4)),
                     Specular(0.2,5,Vect3(0.6,0.6,0.6)),
                     Glossy(0.9,10,Vect3(1,1,1)));
    
    Sphere* sphere = new Sphere(Vect3(3, 0, 0), 3, phong);
    
    Phong* phong2 = new Phong(
                 Lambertian(1,Vect3(0.0,0.3,0)),
                 Lambertian(0.6,Vect3(0,1,0)),
                 Specular(0.2,5,Vect3(1,1,1)));
    
    //
    Sphere* sphere2 = new Sphere(Vect3(-3, -2, -5), 2, phong2);
    
    Phong* phong3 = new Phong(
                 Lambertian(0.25,Vect3(0.3,0,0)),
                 Lambertian(0.6,Vect3(0.8,0,0)),
                 Specular(0.2,5,Vect3(1,1,1)));
    
    //
    Sphere* sphere3 = new Sphere(Vect3(5, 5, -10), 3,phong3);
    
    Phong* planem = new Phong(
                 Lambertian(0.25,Vect3(0.8,0.8,0.8)),
                 Lambertian(0.6,Vect3(0.8,0.8,0.8)),
                 Specular(0.2,5,Vect3(1,1,1)));
    Phong* planeb = new Phong(
                 Lambertian(0.25,Vect3(0.8,0.8,0.8)),
                 Lambertian(0.6,Vect3(0.8,0.8,0.8)),
                 Specular(0.2,1,Vect3(1,1,1)));
    
    Phong* planel = new Phong(
                 Lambertian(0.25,Vect3(0.8,0,0)),
                 Lambertian(0.6,Vect3(0.8,0,0)),
                 Specular(0.2,5,Vect3(1,1,1)));
    Phong* planer = new Phong(
                 Lambertian(0.25,Vect3(0,0.8,0)),
                 Lambertian(0.5,Vect3(0,0.8,0)),
                 Specular(0.2,5,Vect3(1,1,1)));
    
    Plane* planeback = new Plane(Vect3(0, 0, -20), Vect3(0,0,1),planem);
    Plane* planeleft = new Plane(Vect3(-20, 0, 0), Vect3(1,0,0),planel);
    Plane* planeright = new Plane(Vect3(20, 0, 0), Vect3(-1,0,0),planer);
    Plane* planebottom = new Plane(Vect3(0, -10, 0), Vect3(0,1,0),planeb);
    Plane* planetop =  new Plane(Vect3(0, 20, 0), Vect3(0,-1,0),planem);
    
    
    add_object(sphere3);
    add_object(sphere2);
    add_object(sphere);
    add_object(planeback);
    add_object(planeleft);
    add_object(planeright);
    add_object(planebottom);
    add_object(planetop);
    
    add_Light(light2);
}

