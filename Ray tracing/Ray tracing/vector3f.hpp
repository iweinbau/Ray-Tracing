#ifndef vector3f
#define vector3f

#include "math.h"
#include <iostream>
#include <algorithm>
using namespace std;


class Vect3 {
public:
    double x_;
    double y_;
    double z_;
    
    Vect3():x_(0),y_(0),z_(0)
    {}
    
    Vect3(double x, double y, double z):x_(x),y_(y),z_(z)
    {}
    
    Vect3(Vect3 const &v):x_(v.x_),y_(v.y_),z_(v.z_)
    {}
    
    ~Vect3(){}
    Vect3& operator= (Vect3 const& v){
        x_ = v.x_; y_ = v.y_; z_=v.z_;
        return(*this);
    }
    
    double length() {
        return (sqrt(x_ * x_ + y_ * y_ + z_ * z_));
    }
    
    Vect3 normalize() {
        double mag = length();
        return Vect3(x_ /mag, y_ / mag, z_ /mag);
    }
    
    Vect3 neg() {
        return Vect3(-x_,-y_,-z_);
    }
    
    double dot(Vect3 other) {
        return(x_ * other.x_ + y_ * other.y_ + z_ * other.z_);
    }
    
    Vect3 cross(Vect3 other) {
        double x = y_ * other.z_ - z_ * other.y_;
        double y = z_ * other.x_ - x_ * other.z_;
        double z = x_ * other.y_ - y_ * other.x_;
        
        return Vect3(x, y, z);
    }
    
    void print()
    {
        cout << x_ << '/' << y_ << '/' << z_<< endl;
    }
};

Vect3 operator + (const Vect3 & v1, const Vect3 &v2) {
    return Vect3(v1.x_ + v2.x_, v1.y_ + v2.y_, v1.z_ + v2.z_);
}

Vect3 operator - (const Vect3 & v1, const Vect3 &v2){
    return Vect3(v1.x_ - v2.x_, v1.y_ - v2.y_, v1.z_ - v2.z_);
}

Vect3 operator * (const Vect3 & v1, const Vect3 &v2){
    return Vect3(v1.x_ * v2.x_, v1.y_ * v2.y_,v1.z_ * v2.z_);
}

Vect3 operator * (const Vect3 & v1, double const& s) {
    return Vect3(v1.x_ * s, v1.y_ * s,v1.z_ * s);
}

#endif
