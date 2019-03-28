//
//  Triangle.cpp
//  raytracer
//
//  Created by Iwein Bau on 23/02/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#include "Triangle.hpp"
#include "../Utils/Vect3.hpp"
#include "../Utils/ray.hpp"
#include "../Utils/Normal.hpp"



Triangle::Triangle(){

}
Triangle::Triangle(Point3 v0,Point3  v1, Point3  v2,Material* material):Object((v0+v1+v2)/3,material),
_v0(v0),
_v1(v1),
_v2(v2),
_normal((Vect3(v1-v0)).cross(v2-v0).normalize())
{}

Triangle::Triangle(Point3 v0,Point3  v1, Point3  v2):Object((v0+v1+v2)/3),
_v0(v0),
_v1(v1),
_v2(v2),
_normal((Vect3(v1-v0)).cross(v2-v0).normalize())
{}
Triangle::~Triangle(){}

bool Triangle::hit(Ray const& ray, Point3& intersection, double& tmin,Normal& normal){
    double a = _v0.x_ - _v1.x_, b = _v0.x_ - _v2.x_, c = ray.direction_.x_, d = _v0.x_ - ray.origin_.x_;
    double e = _v0.y_ - _v1.y_, f = _v0.y_ - _v2.y_, g = ray.direction_.y_, h = _v0.y_ - ray.origin_.y_;
    double i = _v0.z_ - _v1.z_, j = _v0.z_ - _v2.z_, k = ray.direction_.z_, l = _v0.z_ - ray.origin_.z_;

    double m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
    double q = g * i - e * k, s = e * j - f * i;

    double inv_denom  = 1.0 / (a * m + b * q + c * s);

    double e1 = d * m - b * n - c * p;
    double beta = e1 * inv_denom;

    if (beta < 0.0)
        return (false);

    double r = r = e * l - h * i;
    double e2 = a * n + d * q + c * r;
    double gamma = e2 * inv_denom;

    if (gamma < 0.0 )
        return (false);

    if (beta + gamma > 1.0)
        return (false);

    double e3 = a * p - b * r + d * s;
    double t = e3 * inv_denom;

    if (t < kEpsilon)
        return (false);

    tmin                 = t;
    intersection     = ray.origin_ + ray.direction_ *t;
    normal = _normal;

    return (true);
}

Box Triangle::caluclateBoundingBox(){
  return Box();
};
