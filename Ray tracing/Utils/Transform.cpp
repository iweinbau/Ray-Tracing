//
//  Transform.cpp
//  raytracer
//
//  Created by Iwein Bau on 23/03/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#include "Transform.hpp"
#include "Constants.hpp"
#include "Matrix.hpp"
#include "Point3.hpp"
#include "Normal.hpp"
#include "Vect3.hpp"

Transform::Transform(){
    
}
Transform::~Transform(){
    
}
Vect3 Transform::localToGlobal(Vect3 const& vect){
    return toGlobal * vect;
}
Point3 Transform::localToGlobal(Point3 const& point){
    return toGlobal * point;
}
Normal Transform::localToGlobal(Normal const& normal){
    return toLocal * normal;
}
Vect3 Transform::globalToLocal(Vect3 const& vect){
    return toLocal * vect;
}
Point3 Transform::globalToLocal(Point3 const& point){
    return toLocal * point;
}

void Transform::translate(Vect3 const& translate) {
    
    Matrix4 translation_matrix;
    
    translation_matrix.elements[0][3] = -translate.x_;
    translation_matrix.elements[1][3] = -translate.y_;
    translation_matrix.elements[2][3] = -translate.z_;
    
    toLocal = toLocal * translation_matrix;
    
    translation_matrix.elements[0][3] = translate.x_;
    translation_matrix.elements[1][3] = translate.y_;
    translation_matrix.elements[2][3] = translate.z_;
    
    toGlobal = translation_matrix * toGlobal;
}

void Transform::scale(Vect3 const& scale){
    Matrix4 scale_matrix;
    
    scale_matrix.elements[0][0] = 1/scale.x_;
    scale_matrix.elements[1][1] = 1/scale.y_;
    scale_matrix.elements[2][2] = 1/scale.z_;
    
    toLocal = toLocal * scale_matrix;
    
    scale_matrix.elements[0][0] = scale.x_;
    scale_matrix.elements[1][1] = scale.y_;
    scale_matrix.elements[2][2] = scale.z_;
    
    toGlobal = scale_matrix * toGlobal;
}

void Transform::rotateX(double r){
    //degree to radians
    double cos_theatha = cos(r * PI/180);
    double sin_theatha = sin(r * PI/180);
    
    Matrix4 rotationX_matrix;
    
    rotationX_matrix.elements[1][1] = cos_theatha;
    rotationX_matrix.elements[2][2] = cos_theatha;
    rotationX_matrix.elements[1][2] = sin_theatha;
    rotationX_matrix.elements[2][1] = -sin_theatha;
    
    toLocal = toLocal * rotationX_matrix;
    
    rotationX_matrix.elements[1][2] = -sin_theatha;
    rotationX_matrix.elements[2][1] = sin_theatha;
    
    toGlobal = rotationX_matrix * toGlobal;
    

}
void Transform::rotateY(double r){
    //degree to radians
    double cos_theatha = cos(r * PI/180);
    double sin_theatha = sin(r * PI/180);
    
    Matrix4 rotationY_matrix;
    
    rotationY_matrix.elements[0][0] = cos_theatha;
    rotationY_matrix.elements[0][2] = -sin_theatha;
    rotationY_matrix.elements[2][0] = sin_theatha;
    rotationY_matrix.elements[2][2] = cos_theatha;
    
    toLocal = toLocal * rotationY_matrix;
    
    rotationY_matrix.elements[0][2] = sin_theatha;
    rotationY_matrix.elements[2][0] = -sin_theatha;
    
    toGlobal = rotationY_matrix * toGlobal;
}
void Transform::rotateZ(double r){
    //degree to radians
    double cos_theatha = cos(r * PI/180);
    double sin_theatha = sin(r * PI/180);
    
    Matrix4 rotationZ_matrix;
    
    rotationZ_matrix.elements[0][0] = cos_theatha;
    rotationZ_matrix.elements[1][1] = cos_theatha;
    rotationZ_matrix.elements[1][0] = -sin_theatha;
    rotationZ_matrix.elements[0][1] = sin_theatha;
    
    toLocal = toLocal * rotationZ_matrix;
    
    rotationZ_matrix.elements[0][1] = -sin_theatha;
    rotationZ_matrix.elements[1][0] = sin_theatha;
    
    toGlobal = rotationZ_matrix * toGlobal;
}

