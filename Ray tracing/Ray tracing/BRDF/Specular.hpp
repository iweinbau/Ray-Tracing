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
    Specular(): ks(0.0), cs()
    {}
    
    ~Specular()
    {}
    
    Specular(double factor, Vect3 color): ks(factor), cs(color)
    {}

    //No sampling used here. Used the formula of Bling-Phong light model
    Vect3 sample(Hitinfo const& hitinfo,Vect3 const& ld){
        Vect3 H = (ld + hitinfo.direction.neg()).normalize();
        // Intensity of specular light
        double NdotH = hitinfo.normal.dot(H);
        double intensity = pow(NdotH,ks);
        return cs * intensity;
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
    Vect3 cs;
};

#endif /* Specular_h */
