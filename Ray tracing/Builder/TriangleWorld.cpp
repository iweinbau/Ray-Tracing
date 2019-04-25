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
#include "../Light/pointLight.hpp"
#include "../Objects/Triangle.hpp"
#include "../Material/Phong.hpp"
#include "../Objects/Instance.hpp"

void TriangleWorld::buildWorld(){
    //PointLight light(Vect3(1, 1,1), Vect3(5,5, -5),500);
    PointLight* light = new PointLight(Vect3(1), Vect3(0,0, 3),10);

    add_Light(light);

    Phong* phong = new Phong(
                              Lambertian(1,Vect3(0.0,0.3,0)),
                              Lambertian(0.6,Vect3(0,1,0)),
                              Specular(0.2,5,Vect3(1,1,1)));

    MeshLoader::OBJLoader objLoader;
    objLoader.loadMesh("./Objects/cube.obj");
    Mesh mesh = objLoader.getLoadedMesh();

    for(int i= 0;i<mesh._indices.size();i=i+3){
          Triangle* tri = new Triangle(Point3(mesh._positions[mesh._indices[i]]),
                                        Point3(mesh._positions[mesh._indices[i+1]]),
                                        Point3(mesh._positions[mesh._indices[i+2]]),phong);
          Instance* instance = new Instance(tri,phong);
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

}
