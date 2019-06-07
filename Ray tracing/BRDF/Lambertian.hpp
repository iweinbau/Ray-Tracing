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
    Vect3 f(Hitinfo const& hitinfo,Vect3& wi, Vect3 const& wo){
        return cd * kd * (1/PI);
    }
    
    Vect3 sample_f(Hitinfo const& hitinfo,Vect3& wi, Vect3 const& wo,double& pdf){

        Vect3 w = hitinfo.normal;
        Vect3 v = Vect3(0.0034, 1, 0.0071).cross(w);
        v = v.normalize();
        Vect3 u = v.cross(w);

        
        std::random_device rd;  //Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
        std::uniform_real_distribution<> dis(0.0, 1.0);
        
        //From raytracing from the ground up.
        double x = dis(gen);
        double y = dis(gen);
        
        double cos_phi = cos(2.0 * PI * x);
        double sin_phi = sin(2.0 * PI * x);
        double cos_theta = pow((1.0 - y), 1.0 / (1.0+1.0));
        double sin_theta = sqrt (1.0 - cos_theta * cos_theta);
        
        double pu = sin_theta * cos_phi;
        double pv = sin_theta * sin_phi;
        double pw = cos_theta;
        
        wi = u * pu + v * pv + w * pw;
        wi = wi.normalize();
        
        pdf = hitinfo.normal.dot(wi) * (1/PI);
        
        return (kd * cd * (1/PI));
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
