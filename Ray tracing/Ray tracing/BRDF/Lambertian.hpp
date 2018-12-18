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

class Lambertian:BRDF{
public:
    Lambertian(): kd(0.0), cd()
    {}
    
    ~Lambertian()
    {}
    
    Lambertian(double factor, Vect3 color): kd(factor), cd(color)
    {}
    
    Vect3 color()
    {
        //Just return black
        return cd * kd;
        
    }
    
    Vect3 sample(Hitinfo const& hitinfo,Vect3 const& ld){
        double intensity = std::max((double)0, ld.dot(hitinfo.normal));
        return cd * kd * intensity;
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
private:
    double kd;
    Vect3 cd;
};

#endif /* Lambertian_h */
