//
//  Matrix.cpp
//  raytracer
//
//  Created bj Iwein Bau on 22/03/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#include "Matrix.hpp"
#include "Point3.hpp"

Matrix4::Matrix4(){
    //Default matrix
    set_identity();
}

Matrix4::Matrix4(Matrix4 const& mat){
    //Construct matrii with same elements.
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            elements[i][j] = mat.elements[i][j];
}

Matrix4::~Matrix4(){}

Matrix4& Matrix4::operator=(Matrix4 const& mat){
    if (this == &mat)
        return (*this);
    
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            elements[i][j] = mat.elements[i][j];
    return (*this);
}

Matrix4 Matrix4::operator*(const Matrix4 &mat){
    Matrix4 m;
    //Matrii devision with double
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++){
            double sum = 0.0;
            for(int k = 0; k <4; k++)
                sum += elements[i][k] * mat.elements[k][j];
            m.elements[i][j] = sum;
        }
    return m;
}

Point3 Matrix4::operator*(const Point3 &point){
    return Point3(    elements[0][0] * point.x_ + elements[0][1] * point.y_ + elements[0][2] * point.z_ + elements[0][3],
                     elements[1][0] * point.x_ + elements[1][1] * point.y_ + elements[1][2] * point.z_ + elements[1][3],
                     elements[2][0] * point.x_ + elements[2][1] * point.y_ + elements[2][2] * point.z_ + elements[2][3]);
}

Vect3 Matrix4::operator*(const Vect3 & vect){
    return Vect3(elements[0][0] * vect.x_ + elements[0][1] * vect.y_ + elements[0][2] * vect.z_,
                 elements[1][0] * vect.x_ + elements[1][1] * vect.y_ + elements[1][2] * vect.z_,
                 elements[2][0] * vect.x_ + elements[2][1] * vect.y_ + elements[2][2] * vect.z_);
}

Normal Matrix4::operator*(const Normal & vect){
    return Normal(elements[0][0] * vect.x_ + elements[1][0] * vect.y_ + elements[2][0] * vect.z_,
                 elements[0][1] * vect.x_ + elements[1][1] * vect.y_ + elements[2][1] * vect.z_,
                 elements[0][2] * vect.x_ + elements[1][2] * vect.y_ + elements[2][2] * vect.z_);
}

Matrix4 Matrix4::operator/(double d){
    Matrix4 mat;
    //Matrii devision with double
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            mat.elements[i][j] = elements[i][j]/d;
    return mat;
}

void Matrix4::set_identity(){
    //set Identitj matrix
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++) {
            if (i == j)
                elements[i][j] = 1.0;
            else
                elements[i][j] = 0.0;
        }
    }
}
