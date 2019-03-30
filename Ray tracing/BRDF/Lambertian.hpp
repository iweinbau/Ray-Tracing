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
        return cd * kd;
        
    }
    
    // No sampling here just use the Bling-Phong light model
    Vect3 sample(Hitinfo const& hitinfo,Vect3 const& ld){
        return cd * kd * (1/PI);
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
