//
//  Normal.hpp
//  Ray Tracer
//
//  Created by Iwein Bau on 22/03/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#ifndef Normal_h
#define Normal_h

#include <iostream>
#include "math.h"

class Point3;
class Vect3;

class Normal {
public:
    double x_;
    double y_;
    double z_;
    
    Normal();
    
    Normal(double x, double y, double z);
    
    Normal(Normal const &v);
    
    Normal(Point3 const& p);
    
    Normal(Vect3 const& v);
    
    ~Normal();
    Normal& operator= (Normal const& v);
    
    double length();
    
    Normal normalize();
    
    Normal neg() const;
    
    double dot(Normal const& other)const;
    
    Normal cross(Normal other);
    
    void print()
    {
        std::cout << x_ << '/' << y_ << '/' << z_<< std::endl;
    }
};

inline Normal operator + (const Normal & v1, const Normal &v2) {
    return Normal(v1.x_ + v2.x_, v1.y_ + v2.y_, v1.z_ + v2.z_);
}

inline Normal operator - (const Normal & v1, const Normal &v2){
    return Normal(v1.x_ - v2.x_, v1.y_ - v2.y_, v1.z_ - v2.z_);
}

inline Normal operator * (const Normal & v1, const Normal &v2){
    return Normal(v1.x_ * v2.x_, v1.y_ * v2.y_,v1.z_ * v2.z_);
}

inline Normal operator / (const Normal & v1, double const& s) {
    return Normal(v1.x_ / s, v1.y_ / s,v1.z_ / s);
}


inline Normal operator * (const Normal & v1, double const& s) {
    return Normal(v1.x_ * s, v1.y_ * s,v1.z_ * s);
}


#endif /* Normal_h */
