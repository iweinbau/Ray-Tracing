//
//  Point3.hpp
//  Ray Tracer
//
//  Created by Iwein Bau on 22/03/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#ifndef Point3_h
#define Point3_h

#include "Vect3.hpp"

class Point3 {
public:
    double x_;
    double y_;
    double z_;

    Point3();

    Point3(Vect3);
    
    Point3(double x, double y, double z);

    Point3(Point3 const &v);

    ~Point3();

    Point3& operator= (Point3 const& v);

    Point3 neg() const;

    void print()
    {
        std::cout << x_ << '/' << y_ << '/' << z_<< std::endl;
    }

};

inline Point3 operator + (const Point3 & v1, const Vect3& v2) {
    return Point3(v1.x_ + v2.x_, v1.y_ + v2.y_, v1.z_ + v2.z_);
}

inline Point3 operator - (const Point3 & v1, const Vect3 &v2){
    return Point3(v1.x_ - v2.x_, v1.y_ - v2.y_, v1.z_ - v2.z_);
}

inline Point3 operator * (const Point3 & v1, const Point3 &v2){
    return Point3(v1.x_ * v2.x_, v1.y_ * v2.y_,v1.z_ * v2.z_);
}

inline Point3 operator / (const Point3 & v1, double const& s) {
    return Point3(v1.x_ / s, v1.y_ / s,v1.z_ / s);
}


inline Point3 operator * (const Point3 & v1, double const& s) {
    return Point3(v1.x_ * s, v1.y_ * s,v1.z_ * s);
}

#endif /* Point3_h */
