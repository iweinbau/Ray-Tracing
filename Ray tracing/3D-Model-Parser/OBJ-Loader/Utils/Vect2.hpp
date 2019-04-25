//
//  Vect2.hpp
//  OBJ-Loader
//
//  Created by Iwein Bau on 21/02/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#ifndef Vect2_h
#define Vect2_h

#include "math.h"
#include <iostream>
#include <algorithm>

class Vect2 {
public:
    double x_;
    double y_;
    
    Vect2():x_(0),y_(0)
    {}
    
    Vect2(double x, double y):x_(x),y_(y)
    {}
    
    Vect2(Vect2 const &v):x_(v.x_),y_(v.y_)
    {}
    
    ~Vect2(){}
    Vect2& operator= (Vect2 const& v){
        x_ = v.x_; y_ = v.y_;
        return(*this);
    }
    
    double length() {
        return (sqrt(x_ * x_ + y_ * y_));
    }
    
    Vect2 normalize() {
        double mag = length();
        return Vect2(x_ /mag, y_ / mag);
    }
    
    Vect2 neg() const{
        return Vect2(-x_,-y_);
    }
    
    double dot(Vect2 const& other) const {
        return(x_ * other.x_ + y_ * other.y_);
    }
    
    void print()
    {
        std::cout << x_ << '/' << y_ << std::endl;
    }
};

inline Vect2 operator + (const Vect2 & v1, const Vect2 &v2) {
    return Vect2(v1.x_ + v2.x_, v1.y_ + v2.y_);
}

inline Vect2 operator - (const Vect2 & v1, const Vect2 &v2){
    return Vect2(v1.x_ - v2.x_, v1.y_ - v2.y_);
}

inline Vect2 operator * (const Vect2 & v1, const Vect2 &v2){
    return Vect2(v1.x_ * v2.x_, v1.y_ * v2.y_);
}

inline Vect2 operator / (const Vect2 & v1, double const& s) {
    return Vect2(v1.x_ / s, v1.y_ / s);
}


inline Vect2 operator * (const Vect2 & v1, double const& s) {
    return Vect2(v1.x_ * s, v1.y_ * s);
}
#endif /* Vect2_h */
