//
//  Instance.cpp
//  raytracer
//
//  Created by Iwein Bau on 22/03/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#include "Instance.hpp"

Instance::Instance():Object(),object(),transform(){}

Instance::Instance(Object* obj,Material* mat):Object(mat),object(obj),transform(){}

Instance::~Instance(){
    delete object;
}

//Transformations
void Instance::translate(Vect3 const& translate) {
    transform.translate(translate);
}

void Instance::scale(Vect3 const& scale){
    transform.scale(scale);
}

void Instance::rotateX(double d){
    transform.rotateX(d);
}

void Instance::rotateY(double d){
    transform.rotateY(d);
}

void Instance::rotateZ(double d){
    transform.rotateZ(d);
}


//Hit function
bool Instance::hit(Ray const& ray, Point3& intersection, double& tmin,Normal& normal){
    Ray inv_ray(ray);
    inv_ray.direction_ = transform.globalToLocal(ray.direction_);
    inv_ray.origin_ = transform.globalToLocal(ray.origin_);

    if(object->hit(inv_ray, intersection, tmin,normal)){
        intersection = transform.localToGlobal(intersection);
        normal = transform.localToGlobal(normal);
        normal = normal.normalize();
        return true;
    }
    return false;
}

Box Instance::caluclateBoundingBox(){
    //The fastes way to do this is to get the bounding box of the
    // untransformed object.
    //Then transform this points and find the min and max values of the transformed vertices.
    Box bboxObject = object->caluclateBoundingBox();
    //construct the vertices of the untransfomed bounding box.
    Point3 v[8];
    bboxObject.getVertices(v);
    
    //transform local to global.
    for(int i=0;i<8;i++){
        v[i] = transform.localToGlobal(v[i]);
    }
    
    //find min and max values.
    double min_x = INFINITY,min_y=INFINITY,min_z =INFINITY;
    double max_x=-INFINITY,max_y=-INFINITY,max_z=-INFINITY;
    
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
    
  return Box(Point3(min_x,min_y,min_z), Point3(max_x,max_y,max_z));
};
