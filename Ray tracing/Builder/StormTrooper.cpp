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
#include "../3D-Model-Parser/OBJ-Loader/Loader/OBJ_Loader.h"

#include "../Objects/Grid.hpp"
#include "../Objects/Instance.hpp"


#include "../Material/Disney.hpp"
#include "../Material/Emissive.hpp"
#include "../Material/Phong.hpp"

#include "../BRDF/Lambertian.hpp"
#include "../BRDF/Glossy.hpp"

#include "../Utils/ThinLens.hpp"

void StormTrooper::buildWorld(){
    
    //Camera setup
    //construct a camera
    Point3 lookfrom(-0.283894,-0.794405,9.13327);
    Vect3 lookat(-0.9951571822166443,0.00454461295157671,-0.09819173067808151);
    camera = new ThinLens(lookfrom, lookat, 39.6, 7.7, 0.1);
    
    Disney* boxMat = new Disney();
    boxMat->baseColor = Vect3(0.17);
    boxMat->specular = 0;
    boxMat->roughness =1;
    
    Disney* helmetsMat = new Disney();
    helmetsMat->baseColor = Vect3(1);
    helmetsMat->specular = 1;
    helmetsMat->roughness =0;
    helmetsMat->metallic = 0.4;
    
    Disney* soldierMat = new Disney();
    soldierMat->baseColor = Vect3(0);
    soldierMat->specular = 0;
    
    
    MeshLoader::OBJLoader objLoader;
    objLoader.loadMesh("./Objects/box.obj");
    Mesh mesh = objLoader.getLoadedMesh();
    
    Grid* box = new Grid(mesh,boxMat);
    
    objLoader.loadMesh("./Objects/lights.obj");
    Mesh mesh2 = objLoader.getLoadedMesh();
    
    Grid* lights = new Grid(mesh2,new Emissive(3,Vect3(3.2, 0.13, 0.13)));
    
    objLoader.loadMesh("./Objects/helmets.obj");
    mesh = objLoader.getLoadedMesh();
    Grid* helmets = new Grid(mesh,helmetsMat);
    
    objLoader.loadMesh("./Objects/soldiers.obj");
    mesh = objLoader.getLoadedMesh();
    Grid* soldier = new Grid(mesh,soldierMat);

    add_object(box);
    add_object(lights);
    add_object(helmets);
    add_object(soldier);


}
