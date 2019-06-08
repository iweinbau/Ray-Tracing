//
//  BRDF.hpp
//  Ray-tracer
//
//  Created by Iwein Bau on 17/12/2018.
//  Copyright © 2018 Iwein Bau. All rights reserved.
//

#ifndef BRDF_h
#define BRDF_h

#include "../Utils/Vect3.hpp"
#include "../Utils/Hitinfo.hpp"

class BRDF{
public:
    BRDF()
    {}

    BRDF(BRDF const& other)
    {}

    ~BRDF()
    {}

    virtual Vect3 f(Hitinfo const& hitinfo,Vect3& wi, Vect3 const& wo)
    {
        //Just return black
        return Vect3();
    }
    
    virtual Vect3 sample_f(Hitinfo const& hitinfo,Vect3& wi, Vect3 const& wo,double& pdf){
        return Vect3();
    }

    virtual Vect3 color()
    {
        //Just return black
        return Vect3();
    }
};

#endif /* BRDF_h */