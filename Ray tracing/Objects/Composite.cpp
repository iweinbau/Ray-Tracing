//
//  Composite.cpp
//  raytracer
//
//  Created by Iwein Bau on 29/04/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#include "Composite.hpp"
#include "../Utils/Hitinfo.hpp"

Composite::Composite():Object(){}

Composite::Composite(Material* shader):Object(shader){}
Composite::Composite(Composite const& comp):Object(comp){}

Composite::~Composite(){
    shader_ = NULL;
    for (int i =0; i<objects.size(); i++) {
        delete objects[i];
        objects[i] = NULL;
    }
    objects.erase(objects.cbegin(),objects.cend());
};

Object* Composite::clone() {
    return new Composite(*this);
}

Box Composite::caluclateBoundingBox(){
    //find min and max values.
    double min_x = INFINITY,min_y=INFINITY,min_z =INFINITY;
    double max_x=-INFINITY,max_y=-INFINITY,max_z=-INFINITY;
    
    for (Object* object : objects) {
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
    return Box(Point3(min_x - kEpsilon,min_y - kEpsilon,min_z -kEpsilon), Point3(max_x +kEpsilon,max_y +kEpsilon,max_z+kEpsilon));
}
bool Composite::hit(Ray const& ray, Point3& intersection, double& tmin,Normal& normal){
    double t;
    double tmax = INFINITY;
    Point3 intersect;
    Normal n;
    bool hit = false;
    for(Object* obj : objects){
        if (obj->hit(ray, intersect, t,n)) {
            if (t < tmax) {
                //we found a closer object.
                tmin = t;
                intersection = intersect;
                normal = n;
                shader_ = obj->shader_;
                hit = true;
            }
        }
    }
    return hit;
}
