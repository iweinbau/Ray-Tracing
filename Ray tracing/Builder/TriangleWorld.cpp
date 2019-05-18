//
//  TriangleWorld.cpp
//  raytracer
//
//  Created by Iwein Bau on 17/03/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#include <stdio.h>

#include "./TriangleWorld.hpp"

#include "../3D-Model-Parser/OBJ-Loader/Loader/MeshLoader.hpp"
#include "../3D-Model-Parser/OBJ-Loader/Mesh/Mesh.hpp"

#include "../Objects/Plane.hpp"

#include "../Objects/Triangle.hpp"
#include "../Objects/SmoothTriangle.hpp"
#include "../Objects/Grid.hpp"
#include "../Material/Phong.hpp"
#include "../Material/Reflective.hpp"
#include "../Material/Mirror.hpp"
#include "../Objects/Instance.hpp"
#include "../Objects/Rectangle.hpp"
#include "../Light/pointLight.hpp"
#include "../Light/AreaLight.hpp"

#include "../Material/Disney.hpp"

void TriangleWorld::buildWorld(){
    //PointLight light(Vect3(1, 1,1), Vect3(5,5, -5),500);
    Mirror * reflective = new Mirror(Lambertian(0.25,Vect3(0.3)),
                                   new Lambertian(0.6,Vect3(0.4)),
                                   new Specular(0.9,5,Vect3(0.6)),
                                   new Glossy(1,10,Vect3(1,1,1)));
    
    Sphere* r = new Sphere(Vect3(0,0,6),1);
    AreaLight* light = new AreaLight(r,Vect3(1),10);
    add_Light(light);

    Sphere* sphere = new Sphere(Point3(0, 0, 0), 1);

    Instance* instance = new Instance(sphere,reflective);
    instance->scale(Vect3(2));
    instance->translate(Vect3(0, 0, 0));

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

    add_object(planeback);
    add_object(planeleft);
    add_object(planeright);
    add_object(planebottom);
    add_object(planetop);
    add_object(instance);

}
