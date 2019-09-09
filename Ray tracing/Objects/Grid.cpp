//
//  Grid.cpp
//  raytracer
//
//  Created by Iwein Bau on 28/03/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#include "Grid.hpp"
#include "Composite.hpp"
#include "../Objects/Triangle.hpp"
#include "../Objects/SmoothTriangle.hpp"
#include "../Utils/Math.hpp"
#include <iostream>


Grid::Grid():Composite(){}
Grid::Grid(Mesh const& mesh,Material* material):Composite(material),sharedMaterial(true){
    for(int i= 0;i<mesh._indices.size();i=i+3){
        std::shared_ptr<Object> tri;
        if(mesh.smoothShading){
            tri = std::make_shared<SmoothTriangle>(Point3(mesh._positions[mesh._indices[i]]),
                                     Point3(mesh._positions[mesh._indices[i+1]]),
                                     Point3(mesh._positions[mesh._indices[i+2]]),
                                     Normal(mesh._normals[mesh._indices[i]]),
                                     Normal(mesh._normals[mesh._indices[i+1]]),
                                     Normal(mesh._normals[mesh._indices[i+2]]),material);
        }else{
            tri = std::make_shared<Triangle>(Point3(mesh._positions[mesh._indices[i]]),
                                    Point3(mesh._positions[mesh._indices[i+1]]),
                                    Point3(mesh._positions[mesh._indices[i+2]]),
                                    Normal(mesh._normals[mesh._indices[i]]),material);
        }
        
        add_object(tri);
    }
    constructCells();
}
Grid::~Grid(){
    // If grid represent a triangle mesh then all objects share the same material.
    // then we set all shaders of the objects to NULL to prevent duplicated delete.
    if(sharedMaterial){
        // We delete this here, the destuctor of the super will set this to NULL.
        delete shader_;
        // Set material of objects to null -> they have a shared material
        for(std::shared_ptr<Object> object : objects){
            object->shader_ = NULL;
        }
    }
}

bool Grid::hit(Ray const& ray, Point3& intersection, double& t,Normal& normal){
    double ox = ray.origin_.x_;
    double oy = ray.origin_.y_;
    double oz = ray.origin_.z_;
    double dx = ray.direction_.x_;
    double dy = ray.direction_.y_;
    double dz = ray.direction_.z_;
    
    double x0 = bbox.p1.x_;
    double y0 = bbox.p1.y_;
    double z0 = bbox.p1.z_;
    double x1 = bbox.p2.x_;
    double y1 = bbox.p2.y_;
    double z1 = bbox.p2.z_;
    
    double tx_min, ty_min, tz_min;
    double tx_max, ty_max, tz_max;
    
    // the following code includes modifications from Shirley and Morley (2003)
    
    double a = 1.0 / dx;
    if (a >= 0) {
        tx_min = (x0 - ox) * a;
        tx_max = (x1 - ox) * a;
    }
    else {
        tx_min = (x1 - ox) * a;
        tx_max = (x0 - ox) * a;
    }
    
    double b = 1.0 / dy;
    if (b >= 0) {
        ty_min = (y0 - oy) * b;
        ty_max = (y1 - oy) * b;
    }
    else {
        ty_min = (y1 - oy) * b;
        ty_max = (y0 - oy) * b;
    }
    
    double c = 1.0 / dz;
    if (c >= 0) {
        tz_min = (z0 - oz) * c;
        tz_max = (z1 - oz) * c;
    }
    else {
        tz_min = (z1 - oz) * c;
        tz_max = (z0 - oz) * c;
    }
    
    double t0, t1;
    
    if (tx_min > ty_min)
        t0 = tx_min;
    else
        t0 = ty_min;
    
    if (tz_min > t0)
        t0 = tz_min;
    
    if (tx_max < ty_max)
        t1 = tx_max;
    else
        t1 = ty_max;
    
    if (tz_max < t1)
        t1 = tz_max;
    
    if (t0 > t1)
        return(false);
    
    
    // initial cell coordinates
    
    int ix, iy, iz;
    
    if (bbox.inside(ray.origin_)) {              // does the ray start inside the grid?
        ix = clamp((ox - x0) * Mx / (x1 - x0), 0, Mx - 1);
        iy = clamp((oy - y0) * My / (y1 - y0), 0, My - 1);
        iz = clamp((oz - z0) * Mz / (z1 - z0), 0, Mz - 1);
    }
    else {
        Point3 p = ray.origin_ + t0 * ray.direction_;  // initial hit point with grid's bounding box
        ix = clamp((p.x_ - x0) * Mx / (x1 - x0), 0, Mx - 1);
        iy = clamp((p.y_ - y0) * My / (y1 - y0), 0, My - 1);
        iz = clamp((p.z_ - z0) * Mz / (z1 - z0), 0, Mz - 1);
    }
    
    // ray parameter increments per cell in the x, y, and z directions
    
    double dtx = (tx_max - tx_min) / Mx;
    double dty = (ty_max - ty_min) / My;
    double dtz = (tz_max - tz_min) / Mz;
    
    double     tx_next, ty_next, tz_next;
    int     ix_step, iy_step, iz_step;
    int     ix_stop, iy_stop, iz_stop;
    
    if (dx > 0) {
        tx_next = tx_min + (ix + 1) * dtx;
        ix_step = +1;
        ix_stop = Mx;
    }
    else {
        tx_next = tx_min + (Mx - ix) * dtx;
        ix_step = -1;
        ix_stop = -1;
    }
    
    if (dx == 0.0) {
        tx_next = INFINITY;
        ix_step = -1;
        ix_stop = -1;
    }
    
    
    if (dy > 0) {
        ty_next = ty_min + (iy + 1) * dty;
        iy_step = +1;
        iy_stop = My;
    }
    else {
        ty_next = ty_min + (My - iy) * dty;
        iy_step = -1;
        iy_stop = -1;
    }
    
    if (dy == 0.0) {
        ty_next = INFINITY;
        iy_step = -1;
        iy_stop = -1;
    }
    
    if (dz > 0) {
        tz_next = tz_min + (iz + 1) * dtz;
        iz_step = +1;
        iz_stop = Mz;
    }
    else {
        tz_next = tz_min + (Mz - iz) * dtz;
        iz_step = -1;
        iz_stop = -1;
    }
    
    if (dz == 0.0) {
        tz_next = INFINITY;
        iz_step = -1;
        iz_stop = -1;
    }
    
    
    // traverse the grid
    while (true) {
        std::shared_ptr<Composite> object_ptr = cells[ix + Mx * iy + Mx * My * iz];
        
        if (tx_next < ty_next && tx_next < tz_next) {
            if (object_ptr && object_ptr->hit(ray,intersection, t, normal) && object_ptr->caluclateBoundingBox().inside(intersection)) {
                shader_ = object_ptr->shader_;
                return (true);
            }
            
            tx_next += dtx;
            ix += ix_step;
            
            if (ix == ix_stop)
                return (false);
        }
        else {
            if (ty_next < tz_next) {
                if (object_ptr && object_ptr->hit(ray,intersection,t,normal) && object_ptr->caluclateBoundingBox().inside(intersection)) {
                    shader_ = object_ptr->shader_;
                    return (true);
                }
                
                ty_next += dty;
                iy += iy_step;
                
                if (iy == iy_stop)
                    return (false);
            }
            else {
                if (object_ptr && object_ptr->hit(ray,intersection, t,normal) && object_ptr->caluclateBoundingBox().inside(intersection)) {
                    shader_ = object_ptr->shader_;
                    return (true);
                }
                
                tz_next += dtz;
                iz += iz_step;
                
                if (iz == iz_stop)
                    return (false);
            }
        }
    }
}

void Grid::constructCells(){
    //construct cells based on objects.
    // caclulate the bounding box of this grid.
    //find min and max values.
    double min_x = INFINITY,min_y=INFINITY,min_z =INFINITY;
    double max_x=-INFINITY,max_y=-INFINITY,max_z=-INFINITY;
    for(std::shared_ptr<Object> object : objects){
        Box bboxObject = object->caluclateBoundingBox();
        //construct the vertices of the untransfomed bounding box.
        Point3 v[8];
        bboxObject.getVertices(v);
        for(int i=0;i<8;i++){
            if(v[i].x_ < min_x)
                min_x = v[i].x_;
            if(v[i].y_ < min_y)
                min_y = v[i].y_;
            if(v[i].z_ < min_z)
                min_z = v[i].z_;
            if(v[i].x_ > max_x)
                max_x = v[i].x_;
            if(v[i].y_ > max_y)
                max_y = v[i].y_;
            if(v[i].z_ > max_z)
                max_z = v[i].z_;
        }
    }
    
    Point3 gridMin = Point3(min_x - kEpsilon,min_y - kEpsilon,min_z-kEpsilon);
    Point3 gridMax = Point3(max_x + kEpsilon,max_y + kEpsilon,max_z+kEpsilon);
    
    bbox = Box(gridMin,gridMax);
    
    //find the size of the bounding box and volume of the bounding box.
    double Sx = max_x-min_x,Sy = max_y -min_y,Sz = max_z -min_z;
    
    int N = objects.size();
    double V = Sx * Sy * Sz;
    
    //Use formula Mi = Si * pow( (density * N)/V, 0,333333)
    //where i the correspond to the dimensions x,y,z
    
    Mx = Sx * pow((density * N)/V,0.33333)+1;
    My = Sy * pow((density * N)/V,0.33333)+1;
    Mz = Sz * pow((density * N)/V,0.33333)+1;
    
    int num_cels = Mx*My*Mz;
    
    //create array of the number of cells.
    for(int i =0; i<num_cels;i++)
        cells.push_back(NULL);
    
    for(std::shared_ptr<Object> obj : objects){
        //find cells that overlap with bounding box.
        Box objBox = obj->caluclateBoundingBox();
        
        Point3 min_distance = objBox.p1 - gridMin;
        Point3 max_distance = objBox.p2 - gridMin;
        
        //calculate index.
        int ix_min = clamp( (min_distance.x_/Sx) *Mx, 0, Mx-1);
        int iy_min = clamp( (min_distance.y_/Sy) *My, 0, My-1);
        int iz_min = clamp( (min_distance.z_/Sz) *Mz, 0, Mz-1);
        
        int ix_max = clamp( (max_distance.x_/Sx) *Mx, 0, Mx-1);
        int iy_max = clamp( (max_distance.y_/Sy) *My, 0, My-1);
        int iz_max = clamp( (max_distance.z_/Sz) *Mz, 0, Mz-1);
        
        for(int iz = iz_min; iz<=iz_max; iz++){
            for(int iy = iy_min; iy<=iy_max; iy++){
                for(int ix = ix_min; ix<=ix_max; ix++){
                    int i = ix + Mx * iy + Mx * My * iz;
                    if(cells[i]){
                        cells[i]->add_object(obj);
                    }else{
                        cells[i] = std::make_shared<Composite>();
                        cells[i]->add_object(obj);
                    }
                }
            }
        }
    }

}

Box Grid::caluclateBoundingBox(){
    return bbox;
}
