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
#include "../Light/Directional.hpp"
#include "../Light/AreaLight.hpp"




//Constructor
World::World(){}
World::~World(){}

void World::buildWorld(){
    //World setup

    //Directional* light = new Directional(Vect3(0, 1,0), Vect3(1),5);
    Sphere* r = new Sphere(Vect3(0,0,6),1);
    AreaLight* light = new AreaLight(r,Vect3(1),5);
    add_Light(light);
    
    ambientLight = AmbientLight(0,Vect3(1),1);

    Mirror * reflective = new Mirror(Lambertian(0.25,Vect3(0.3)),
                                     new Lambertian(0.6,Vect3(0.4)),
                                     new Specular(0.9,5,Vect3(0.6)),
                                     new Glossy(0.9,Vect3(1,1,1)));
    
    Phong* phong2 = new Phong(
                              Lambertian(1,Vect3(0.0,0.3,0)),
                              new Lambertian(0.6,Vect3(0,1,0)),
                              new Specular(0.2,5,Vect3(1,1,1)));
    Phong* phong3 = new Phong(
                              Lambertian(0.25,Vect3(0.3,0,0)),
                              new Lambertian(0.6,Vect3(0.8,0,0)),
                              new Specular(0.2,5,Vect3(1,1,1)));

    Sphere* sphere = new Sphere(Point3(0, 0, 0), 1);

    Instance* s = new Instance(sphere,reflective);
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
                 new Lambertian(0.6,Vect3(0.8,0.8,0.8)),
                 new Specular(0.2,5,Vect3(1,1,1)));
    Phong* planeb = new Phong(
                 Lambertian(0.25,Vect3(0.8,0.8,0.8)),
                 new Lambertian(0.6,Vect3(0.8,0.8,0.8)),
                 new Specular(0.2,1,Vect3(1,1,1)));

    Phong* planel = new Phong(
                 Lambertian(0.25,Vect3(0.8,0,0)),
                 new Lambertian(0.6,Vect3(0.8,0,0)),
                 new Specular(0.2,5,Vect3(1,1,1)));
    Phong* planer = new Phong(
                 Lambertian(0.25,Vect3(0,0.8,0)),
                 new Lambertian(0.5,Vect3(0,0.8,0)),
                 new Specular(0.2,5,Vect3(1,1,1)));

    Plane* planeback = new Plane(Point3(0, 0, -5), Normal(0,0,1),planem);
    Plane* planeleft = new Plane(Point3(-5, 0, 0), Normal(1,0,0),planel);
    Plane* planeright = new Plane(Point3(5, 0, 0), Normal(-1,0,0),planer);
    Plane* planebottom = new Plane(Point3(0, -5, 0), Normal(0,1,0),planeb);
    Plane* planetop =  new Plane(Point3(0, 5, 0), Normal(0,-1,0),planem);


    add_object(s3);
    add_object(s2);
    add_object(s);
    add_object(planeback);
    add_object(planeleft);
    add_object(planeright);
    add_object(planebottom);
    add_object(planetop);

    add_Light(light);
}
