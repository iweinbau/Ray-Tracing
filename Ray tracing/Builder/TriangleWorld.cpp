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
    
    //Camera setup
    //construct a camera
    Point3 lookfrom(0,0,10);
    Vect3 lookat(0,0,0);
    camera = new Camera(lookfrom, lookat, 90);
    
    Grid* grid = new Grid();
    grid->add_object(std::make_shared<Sphere>(Point3(-0.5, 0, 0), 1,new Disney()));
    grid->add_object(std::make_shared<Sphere>(Point3(0.5, 0, 0), 1,new Disney()));
    grid->constructCells();
    
    add_object(grid);

}
