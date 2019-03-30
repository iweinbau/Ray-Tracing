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
#include "../Objects/Instance.hpp"

#include "../Light/pointLight.hpp"


//Constructor
World::World(){}
World::~World(){}

void World::buildWorld(){
    //World setup
    
    //PointLight light(Vect3(1, 1,1), Vect3(5,5, -5),500);
    PointLight* light2 = new PointLight(Vect3(0.8, 0.8,0.8), Vect3(-5,0, 5),3);
    
    Reflective* phong = new Reflective(
                     Lambertian(0.25,Vect3(0.3,0.3,0.3)),
                     Lambertian(0.6,Vect3(0.4,0.4,0.4)),
                     Specular(0.2,5,Vect3(0.6,0.6,0.6)),
                     Glossy(0.9,10,Vect3(1,1,1)));
    Phong* phong2 = new Phong(
                              Lambertian(1,Vect3(0.0,0.3,0)),
                              Lambertian(0.6,Vect3(0,1,0)),
                              Specular(0.2,5,Vect3(1,1,1)));
    Phong* phong3 = new Phong(
                              Lambertian(0.25,Vect3(0.3,0,0)),
                              Lambertian(0.6,Vect3(0.8,0,0)),
                              Specular(0.2,5,Vect3(1,1,1)));
    
    Sphere* sphere = new Sphere(Point3(0, 0, 0), 1);

    Instance* s = new Instance(sphere,phong);
    s->scale(Vect3(3));
    s->translate(Vect3(3, 0, 0));
    
    Instance* s2 = new Instance(sphere,phong2);
    s2->scale(Vect3(2,3,2));
    s2->translate(Vect3(-3, -2, -5));
    
    Instance* s3 = new Instance(sphere,phong3);
    s3->scale(Vect3(3));
    s3->translate(Vect3(5, 5, -10));
    

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
    
    Plane* planeback = new Plane(Point3(0, 0, -20), Normal(0,0,1),planem);
    Plane* planeleft = new Plane(Point3(-20, 0, 0), Normal(1,0,0),planel);
    Plane* planeright = new Plane(Point3(20, 0, 0), Normal(-1,0,0),planer);
    Plane* planebottom = new Plane(Point3(0, -10, 0), Normal(0,1,0),planeb);
    Plane* planetop =  new Plane(Point3(0, 20, 0), Normal(0,-1,0),planem);
    
    
    add_object(s3);
    add_object(s2);
    add_object(s);
    add_object(planeback);
    add_object(planeleft);
    add_object(planeright);
    add_object(planebottom);
    add_object(planetop);
    
    add_Light(light2);
}

