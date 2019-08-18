//
//  Sampler.cpp
//  Ray-tracing
//
//  Created by Iwein Bau on 19/06/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#include "Sampler.hpp"
#include "../Utils/Point3.hpp"
#include "../Utils/Constants.hpp"

Sampler::Sampler(){
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    gen = std::mt19937(rd()); //Standard mersenne_twister_engine seeded with rd()
    dis = std::uniform_real_distribution<>(0.0, 1.0);
}

Sampler::~Sampler(){
    
}

Point3 Sampler::sampleOnHemisphere(double exp){
    double x = dis(gen);
    double y = dis(gen);
    
    double cos_phi = cos(2.0 * PI * x);
    double sin_phi = sin(2.0 * PI * x);
    double cos_theta = pow((1.0 - y), 1.0 / (exp + 1.0));
    double sin_theta = sqrt (1.0 - cos_theta * cos_theta);
    
    double pu = sin_theta * cos_phi;
    double pv = sin_theta * sin_phi;
    double pw = cos_theta;
    
    return Point3(pu,pv,pw);
}

Vect2 Sampler::samplePointOnUnitDisk(){
    double r = dis(gen); // radius [0,1]
    double w = dis(gen) * 2 * PI; // angle [0,2*PI]
    
    return Vect2(sqrt(r) * cos(w), sqrt(r) * sin(w));
}


double Sampler::sample(){
    return dis(gen);
}

