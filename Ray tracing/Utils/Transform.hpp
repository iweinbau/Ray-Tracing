//
//  Transform.hpp
//  raytracer
//
//  Created by Iwein Bau on 23/03/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#ifndef Transform_hpp
#define Transform_hpp

#include "Matrix.hpp"
class Vect3;
class Point3;
class Normal;

class Transform{
public:
    Transform();
    ~Transform();
    Vect3 localToGlobal(Vect3 const& vect);
    Point3 localToGlobal(Point3 const& point);
    Normal localToGlobal(Normal const& normal);
    Vect3 globalToLocal(Vect3 const& vect);
    Point3 globalToLocal(Point3 const& point);
    Normal globalToLocal(Normal const& normal);
    
    //Transformations;
    void translate(Vect3 const& vect);
    void scale(Vect3 const& scale);
    void rotateX(double r);
    void rotateY(double r);
    void rotateZ(double r);
private:
    //transformation matrix.
    Matrix4 toGlobal;
    //invers transformation matrix.
    Matrix4 toLocal;
    
};

#endif /* Transform_hpp */
