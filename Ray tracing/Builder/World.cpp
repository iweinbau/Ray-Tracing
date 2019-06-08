//
//  World.cpp
//  raytracer
//
//  Created by Iwein Bau on 25/02/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//


#include "./World.hpp"

#include "../Material/Mirror.hpp"
#include "../Material/Matte.hpp"
#include "../Material/Reflective.hpp"
#include "../Material/Matte.hpp"
#include "../Material/Emissive.hpp"


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
    Sphere* r = new Sphere(Vect3(0,4,0),1,new Emissive(10,Vect3(1)));
    AreaLight* light = new AreaLight(r,Vect3(1),10);
    r->setShadowCast(false);
    //PointLight* light = new PointLight(Vect3(1, 1,1), Vect3(-2,0, 2),10);

    add_Light(light);
    
    ambientLight = AmbientLight(1,Vect3(1),1);

    Reflective * reflective = new Reflective(Lambertian(0.25,Vect3(1,1,0.3)),
                                     new Lambertian(0.6,Vect3(1,1,0.3)),
                                     new Glossy(0.5,20,Vect3(1,1,0.3)),
                                     new Glossy(0.3,100,Vect3(1,1,0.3)));
    
    Matte* Matte2 = new Matte(
                              Lambertian(1,Vect3(0.0,0.3,0)),
                              new Lambertian(0.5,Vect3(0,1,0)));
    Matte* Matte3 = new Matte(
                              Lambertian(0.25,Vect3(0.3,0,0)),
                              new Lambertian(0.5,Vect3(0.8,0,0)));

    Sphere* sphere = new Sphere(Point3(0, 0, 0), 1);

    Instance* s = new Instance(sphere,reflective);
    s->scale(Vect3(5));
    s->translate(Vect3(0, 0, -8));

    Instance* s2 = new Instance(sphere,Matte2);
    s2->scale(Vect3(2,3,2));
    s2->translate(Vect3(-3, -2, -3));

    Instance* s3 = new Instance(sphere,Matte3);
    s3->scale(Vect3(3));
    s3->translate(Vect3(3,-2, -2));


    Matte* planem = new Matte(
                 Lambertian(0.25,Vect3(1)),
                 new Lambertian(0.5,Vect3(1)));
    Matte* planeb = new Matte(
                 Lambertian(0.25,Vect3(1)),
                 new Lambertian(0.5,Vect3(1)));

    Matte* planel = new Matte(
                 Lambertian(0.25,Vect3(1,0,0)),
                 new Lambertian(0.5,Vect3(1,0,0)));
    Matte* planer = new Matte(
                 Lambertian(0.25,Vect3(0,1,0)),
                 new Lambertian(0.5,Vect3(0,1,0)));

    Plane* planeback = new Plane(Point3(0, 0, -5), Normal(0,0,1),planem);
    Plane* planeleft = new Plane(Point3(-5, 0, 0), Normal(1,0,0),planel);
    Plane* planeright = new Plane(Point3(5, 0, 0), Normal(-1,0,0),planer);
    Plane* planebottom = new Plane(Point3(0, -5, 0), Normal(0,1,0),planeb);
    Plane* planetop =  new Plane(Point3(0, 5, 0), Normal(0,-1,0),planem);


    add_object(s3);
    add_object(s2);
    add_object(s);
    add_object(r);
    add_object(planeback);
    add_object(planeleft);
    add_object(planeright);
    add_object(planebottom);
    add_object(planetop);

    add_Light(light);
}