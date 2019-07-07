#ifndef vector3f
#define vector3f

#include "math.h"
#include <iostream>
#include <algorithm>

class Point3;
class Normal;

class Vect3 {
public:
    double x_;
    double y_;
    double z_;

    Vect3();

    Vect3(double x, double y, double z);

    Vect3(double x);

    Vect3(Vect3 const &v);

    Vect3(Point3 const& p);

    Vect3(Normal const& p);

    ~Vect3();
    Vect3& operator= (Vect3 const& v);

    double length();

    Vect3 normalize();

    Vect3 neg() const;

    double dot(Vect3 const& other)const;

    Vect3 cross(Vect3 other);

    void print()
    {
        std::cout << x_ << '/' << y_ << '/' << z_<< std::endl;
    }
};

inline Vect3 operator + (const Vect3 & v1, const Vect3 &v2) {
    return Vect3(v1.x_ + v2.x_, v1.y_ + v2.y_, v1.z_ + v2.z_);
}

inline Vect3 operator - (const Vect3 & v1, const Vect3 &v2){
    return Vect3(v1.x_ - v2.x_, v1.y_ - v2.y_, v1.z_ - v2.z_);
}

inline Vect3 operator * (const Vect3 & v1, const Vect3 &v2){
    return Vect3(v1.x_ * v2.x_, v1.y_ * v2.y_,v1.z_ * v2.z_);
}

inline Vect3 operator / (const Vect3 & v1, double const& s) {
    return Vect3(v1.x_ / s, v1.y_ / s,v1.z_ / s);
}


inline Vect3 operator * (const Vect3 & v1, double const& s) {
    return Vect3(v1.x_ * s, v1.y_ * s,v1.z_ * s);
}

#endif
