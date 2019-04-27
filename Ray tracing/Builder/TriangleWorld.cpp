//
//  TriangleWorld.cpp
//  raytracer
//
//  Created by Iwein Bau on 17/03/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#include <stdio.h>

#include "../3D-Model-Parser/OBJ-Loader/Loader/MeshLoader.hpp"
#include "../3D-Model-Parser/OBJ-Loader/Mesh/Mesh.hpp"

#include "./TriangleWorld.hpp"
#include "../Objects/Plane.hpp"
#include "../Light/pointLight.hpp"
#include "../Objects/Triangle.hpp"
#include "../Objects/SmoothTriangle.hpp"
#include "../Material/Phong.hpp"
#include "../Material/Reflective.hpp"
#include "../Objects/Instance.hpp"

void TriangleWorld::buildWorld(){
    //PointLight light(Vect3(1, 1,1), Vect3(5,5, -5),500);
    PointLight* light = new PointLight(Vect3(1), Vect3(0,0, 3),10);

    add_Light(light);

    Reflective * reflective = new Reflective(
                                       Lambertian(0.25,Vect3(0.3,0.3,0.3)),
                                       Lambertian(0.6,Vect3(0.4,0.4,0.4)),
                                       Specular(0.2,5,Vect3(0.6,0.6,0.6)),
                                       Glossy(0.9,10,Vect3(1,1,1)));

    MeshLoader::OBJLoader objLoader;
    objLoader.loadMesh("./Objects/sphereS.obj");
    Mesh mesh = objLoader.getLoadedMesh();

    for(int i= 0;i<mesh._indices.size();i=i+3){
        Triangle* tri;
        if(mesh.smoothShading){
            tri = new SmoothTriangle(Point3(mesh._positions[mesh._indices[i]]),
                                           Point3(mesh._positions[mesh._indices[i+1]]),
                                           Point3(mesh._positions[mesh._indices[i+2]]),reflective);
        }else{
            tri = new Triangle(Point3(mesh._positions[mesh._indices[i]]),
                                         Point3(mesh._positions[mesh._indices[i+1]]),
                                         Point3(mesh._positions[mesh._indices[i+2]]),reflective);
        }
        Instance* instance = new Instance(tri,reflective);
        instance->rotateY(45);
        instance->rotateX(45);

        add_object(instance);
    }

    //    Triangle(Vect3 v0,Vect3 v1, Vect3 v2,Material* material);
    // Triangle vertices are defined counter clock wise.
    //Triangle* tri = new Triangle(Point3(0, 2, 3), Point3(-2, 0, 3),Point3(2, 0, 3));

    //Instance* instance = new Instance(tri,phong);
    //instance->translate(Vect3(3,0,0));

    //add_object(instance);
    
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

}
