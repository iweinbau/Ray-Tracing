//
//  Specular.hpp
//  Ray-tracer
//
//  Created by Iwein Bau on 17/12/2018.
//  Copyright © 2018 Iwein Bau. All rights reserved.
//

#ifndef Specular_h
#define Specular_h

#include "BRDF.hpp"

class Specular:BRDF{
public:
    Specular(): ks(1),e(0), cs()
    {}
    
    ~Specular()
    {}
    
    Specular(double factor, double exp, Vect3 color): ks(factor),e(exp),cs(color)
    {}
    
    Specular(double factor, Vect3 color): ks(factor),e(0),cs(color)
    {}

    //No sampling used here. Used the formula of Bling-Phong light model
    Vect3 sample(Hitinfo const& hitinfo,Vect3 const& ld, Vect3& out){
        
        out = ld.neg() + (hitinfo.normal * ld.dot(hitinfo.normal) * 2);
        
//        Vect3 H = (ld + hitinfo.direction.neg()).normalize();
//        // Intensity of specular light
        double RdotV = std::max(0.0,out.dot(hitinfo.direction.neg()));
        return cs * ks * pow(RdotV,e);
    }
    
    Vect3 color()
    {
        //Just return black
        return cs * ks;
        
    }
    
    Specular& operator= (Specular const& spec)
    {
        if( this == &spec)
            return (*this);
        
        BRDF::operator=(spec);
        
        ks = spec.ks;
        cs = spec.cs;
        
        return (*this);
    }
    
private:
    double ks;
    double e;
    Vect3 cs;
};

#endif /* Specular_h */
