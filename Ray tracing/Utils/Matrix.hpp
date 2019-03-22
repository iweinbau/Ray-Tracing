//
//  Matrix.hpp
//  raytracer
//
//  Created by Iwein Bau on 22/03/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#ifndef Matrix_hpp
#define Matrix_hpp

#include "Vect3.hpp"
#include "Point3.hpp"
#include "Normal.hpp"

class Matrix4{
public:
    double elements[4][4];
    Matrix4();
    Matrix4(Matrix4 const& matrix);
    ~Matrix4();
    
    Matrix4& operator = (Matrix4 const& matrix);
    Matrix4 operator * (Matrix4 const& matrix);
    //matrix vector multiplication.
    Vect3 operator * (Vect3 const& vect);
    Point3 operator*(const Point3 & point);
    Normal operator*(const Normal & normal);


    Matrix4 operator / (double d);
    void set_identity();
    
};

#endif /* Matrix_hpp */
