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

    //
    Vect3 f(Hitinfo const& hitinfo,Vect3& wi, Vect3 const& wo){
        return Vect3();
    }
    
    //Perfect mirror BRDF.
    Vect3 sample_f(Hitinfo const& hitinfo,Vect3& wi, Vect3 const& wo,double& pdf){
        wi = hitinfo.direction - ( Vect3(hitinfo.normal) * 2 * hitinfo.direction.dot(Vect3(hitinfo.normal)));
        pdf = hitinfo.normal.dot(wi);
        return cs * ks;
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

public:
    double ks;
    double e;
    Vect3 cs;
};

#endif /* Specular_h */
