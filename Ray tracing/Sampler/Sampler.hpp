//
//  Sampler.hpp
//  Ray-tracing
//
//  Created by Iwein Bau on 19/06/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//
//
//  Utility class for creating all sorts of samples, random double, random sample on hemisphere, ...
//

#ifndef Sampler_hpp
#define Sampler_hpp

#include <random>
#include "../3D-Model-Parser/OBJ-Loader/Utils/Vect2.hpp"

class Point3;

class Sampler{
public:
    /**
     *  Constructor create new instance of a Sampler.
     */
    Sampler();
    
    /**
     *  Destructor.
     */
    ~Sampler();
    
    /**
     *  Samples random point on hemisphere following a cos distribution with a given exp.
     *  @param exp The exponent of the distribution.
     *  @return Point3 sampled point.
     */
    Point3 sampleOnHemisphere(double exp=1);
    
    /**
     *  Samples point on unit disk.
     *  @return Vect2 coordinates of the point on the disk.
     */
    Vect2 samplePointOnUnitDisk();
    
    /**
     *  Samples a random number between 0 and 1
     *  @return double random double between 0 and 1.
     */
    double sample();
    
    Sampler& operator= (Sampler const& s);
    
private:
    std::mt19937 gen; //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis;
    
};

inline Sampler& Sampler::operator= (Sampler const& s)
{
    if( this == &s)
        return (*this);
    
    gen = s.gen;
    dis = s.dis;
    return (*this);
}

#endif /* Sampler_hpp */
