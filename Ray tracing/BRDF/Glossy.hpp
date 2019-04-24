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
    
    //perfect reflection
    Vect3 sample(Hitinfo const& hitinfo,Vect3& r){
        r = hitinfo.direction - ( Vect3(hitinfo.normal) * 2 * hitinfo.direction.dot(Vect3(hitinfo.normal)));
        return cs * ks;
    }
    
    //glossy reflection.
    Vect3 sample_(Hitinfo const& hitinfo,Vect3& out,double& pdf){
        
        Vect3 r = hitinfo.direction - ( Vect3(hitinfo.normal) * 2 * hitinfo.direction.dot(Vect3(hitinfo.normal)));
        
        Vect3 w = r;
        Vect3 u = Vect3(0.00424, 1, 0.00764).cross(w);
        u.normalize();
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
        
        out = u * pu + v * pv + w * pw;
        
        if (hitinfo.normal.dot(out) < 0.0)                         // reflected ray is below tangent plane
            out = u * - pu + v * -pv + w * pw;
        
        pdf = 1;
    
        double lobe = std::pow(r.dot(out),e);
        pdf = lobe * hitinfo.normal.dot(out);
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
