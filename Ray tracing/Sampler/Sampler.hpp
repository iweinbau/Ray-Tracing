//
//  Sampler.hpp
//  Ray-tracing
//
//  Created by Iwein Bau on 19/06/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#ifndef Sampler_hpp
#define Sampler_hpp

#include <random>

class Point3;

class Sampler{
public:
    Sampler();
    ~Sampler();
    
    Point3 sampleOnHemisphere(double exp=1);
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
