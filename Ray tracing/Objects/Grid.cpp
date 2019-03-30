//
//  Grid.cpp
//  raytracer
//
//  Created by Iwein Bau on 28/03/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#include "Grid.hpp"

Grid::Grid(){}
Grid::~Grid(){}
bool Grid::hit(Ray const& ray, Point3& intersection, double& tmin,Normal& normal){
    return false;
}
void Grid::add_object(Object* object){
    objects.push_back(object);
}

void Grid::constructCells(){
    //construct cells based on objects.
}
