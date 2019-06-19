//
//  Lambertian.hpp
//  Ray-tracer
//
//  Created by Iwein Bau on 17/12/2018.
//  Copyright © 2018 Iwein Bau. All rights reserved.
//

#ifndef Lambertian_h
#define Lambertian_h

#include "BRDF.hpp"
#include "../Utils/Constants.hpp"

class Lambertian:BRDF<Material>{
public:
    Lambertian(): kd(0.0), cd()
    {}

    ~Lambertian()
    {}

    Lambertian(double factor, Vect3 color): kd(factor), cd(color)
    {}

    Vect3 color()
    {
        return cd * kd;

    }

    // No sampling here just use the Bling-Phong light model
    Vect3 f(Hitinfo const& hitinfo,Vect3& wi, Vect3 const& wo){
        return cd * kd * (1/PI);
    }
    
    double pdf(Material* mat,Hitinfo const& hitinfo, Vect3 const& wi, Vect3 const& wo){
        return hitinfo.normal.dot(wi) * (1/PI);
    }
    
    Vect3 sample_f(Material* mat,Hitinfo const& hitinfo, Vect3 const& wo){
        Vect3 w = hitinfo.normal;
        Vect3 v = Vect3(0.0034, 1, 0.0071).cross(w);
        v = v.normalize();
        Vect3 u = v.cross(w);
        
        Point3 p = sampler.sampleOnHemisphere();
        
        Vect3 wi = u * p.x_ + v * p.y_ + w * p.z_;
        return wi.normalize();
    }
    
    Vect3 eval(Material* mat,Hitinfo const& hitinfo,Vect3 const& wi,Vect3 const& wo){
        return (kd * cd * (1/PI));
    }

    Lambertian& operator= (Lambertian const& lam)
    {
        if( this == &lam)
            return (*this);

        BRDF::operator=(lam);

        kd = lam.kd;
        cd = lam.cd;

        return (*this);
    }
public:
    double kd;
    Vect3 cd;
};

#endif /* Lambertian_h */
