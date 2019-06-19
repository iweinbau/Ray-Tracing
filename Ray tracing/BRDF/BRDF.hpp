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

#include "../Material/Material.hpp"

#include "../Sampler/Sampler.hpp"

template <class M>
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
    
    virtual Vect3 sample_f(M* mat,Hitinfo const& hitinfo, Vect3 const& wo){
        return Vect3();
    }

    virtual Vect3 color()
    {
        //Just return black
        return Vect3();
    }
    
    BRDF<M>& operator= (BRDF<M> const& brdf)
    {
        if( this == &brdf)
            return (*this);
        
        sampler = brdf.sampler;
        return (*this);
    }
    
    virtual double pdf(M* mat,Hitinfo const& hitinfo, Vect3 const& wi, Vect3 const& wo)=0;
        
    virtual Vect3 eval(M* mat,Hitinfo const& hitinfo,Vect3 const& wi,Vect3 const& wo)=0;
    
protected:
    Sampler sampler;
};

#endif /* BRDF_h */
