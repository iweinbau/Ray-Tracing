//
//  StormTrooper.cpp
//  raytracer
//
//  Created by Iwein Bau on 10/06/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#include "StormTrooper.hpp"
#include "../3D-Model-Parser/OBJ-Loader/Loader/MeshLoader.hpp"
#include "../3D-Model-Parser/OBJ-Loader/Mesh/Mesh.hpp"

#include "../Objects/Grid.hpp"

#include "../Material/Disney.hpp"
#include "../Material/Emissive.hpp"
#include "../Material/Phong.hpp"

#include "../BRDF/Lambertian.hpp"
#include "../BRDF/Glossy.hpp"

void StormTrooper::buildWorld(){
    
    MeshLoader::OBJLoader objLoader;
    objLoader.loadMesh("./Objects/box.obj");
    Mesh mesh = objLoader.getLoadedMesh();
    
    Disney* boxMat = new Disney();
    boxMat->baseColor = Vect3(0.17);
    boxMat->specular = 0;
    boxMat->roughness =1;
    
    Grid* box = new Grid(mesh,boxMat);
    
    objLoader.loadMesh("./Objects/lights.obj");
    Mesh mesh2 = objLoader.getLoadedMesh();
    
    Grid* lights = new Grid(mesh2,new Emissive(1,Vect3(3.2, 0.13, 0.13)));
    
    objLoader.loadMesh("./Objects/helmets.obj");
    Mesh mesh3 = objLoader.getLoadedMesh();
    
    Disney* helmetsMat = new Disney();
    helmetsMat->baseColor = Vect3(1);
    helmetsMat->specular = 1;
    helmetsMat->roughness =0;
    helmetsMat->metallic = 0.4;
    
    Grid* helmets = new Grid(mesh3,helmetsMat);
    
    
    add_object(box);
    add_object(lights);
    add_object(helmets);

    
}
