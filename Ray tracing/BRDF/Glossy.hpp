//
//  Glossy.hpp
//  Ray-tracer
//
//  Created by Iwein Bau on 01/02/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#ifndef Glossy_h
#define Glossy_h

#include <random>
#include <iostream>

#include "../Utils/Constants.hpp"
#include "../BRDF/BRDF.hpp"


class Glossy:BRDF{
public:
    Glossy(): ks(1.0),cs(1,1,1)
    {}

    ~Glossy()
    {}

    Glossy(double factor,double exp, Vect3 color): ks(factor),e(exp), cs(color)
    {}
    
    Glossy(double factor,Vect3 color): ks(factor),e(0), cs(color)
    {}
    
    //specular BRDF
    Vect3 f(Hitinfo const& hitinfo,Vect3& wi, Vect3 const& wo){
        Vect3 r = wi.neg() + (Vect3(hitinfo.normal) * wi.dot(Vect3(hitinfo.normal)) * 2);
        double RdotV = std::max(0.0,r.dot(wo));
        return cs * ks * pow(RdotV,e);
    }


    //Sampling specular BRDF.
    Vect3 sample_f(Hitinfo const& hitinfo,Vect3& wi,Vect3 const& wo,double& pdf){
        
        double ndotwo = hitinfo.normal.dot(wo);
        Vect3 r = wo.neg() + hitinfo.normal * 2 * ndotwo;

        Vect3 w = r;
        Vect3 u = Vect3(0.00424, 1, 0.00764).cross(w);
        u = u.normalize();
        Vect3 v = u.cross(w);

        std::random_device rd;  //Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
        std::uniform_real_distribution<> dis(0.0, 1.0);

        //From raytracing from the ground up.
        double x = dis(gen);
        double y = dis(gen);

        double cos_phi = cos(2.0 * PI * x);
        double sin_phi = sin(2.0 * PI * x);
        double cos_theta = pow((1.0 - y), 1.0 / (e + 1.0));
        double sin_theta = sqrt (1.0 - cos_theta * cos_theta);

        double pu = sin_theta * cos_phi;
        double pv = sin_theta * sin_phi;
        double pw = cos_theta;

        wi = u * pu + v * pv + w * pw;

        if (hitinfo.normal.dot(wi) < 0.0)                         // reflected ray is below tangent plane
            wi = u * - pu + v * -pv + w * pw;
        
        wi = wi.normalize();

        double lobe = std::pow(r.dot(wi),e);
        pdf = lobe * (hitinfo.normal.dot(wi));
        return cs * ks * lobe;

    }

    Vect3 color()
    {
        return cs * ks;

    }

    Glossy& operator= (Glossy const& glos)
    {
        if( this == &glos)
            return (*this);

        BRDF::operator=(glos);

        ks = glos.ks;
        cs = glos.cs;

        return (*this);
    }

private:
    double e;
    double ks;
    Vect3 cs;
};

#endif /* Glossy_h */
