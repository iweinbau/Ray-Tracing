//
//  Glossy.hpp
//  Ray-tracer
//
//  Created by Iwein Bau on 01/02/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#ifndef Glossy_h
#define Glossy_h

#include <iostream>

#include "../Utils/Constants.hpp"
#include "../BRDF/BRDF.hpp"
class Glossy:BRDF<Material>{
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
    
    Vect3 sample_f(Material* mat,Hitinfo const& hitinfo, Vect3 const& wo){
        double ndotwo = hitinfo.normal.dot(wo);
        Vect3 r = wo.neg() + hitinfo.normal * 2 * ndotwo;
        
        Vect3 w = r;
        Vect3 u = Vect3(0.00424, 1, 0.00764).cross(w);
        u = u.normalize();
        Vect3 v = u.cross(w);
        
        Point3 p = sampler.sampleOnHemisphere(e);
        
        Vect3 wi = u * p.x_ + v * p.y_ + w * p.z_;
        if (hitinfo.normal.dot(wi) < 0.0)                         // reflected ray is below tangent plane
            wi = u * - p.x_ + v * -p.y_ + w * p.z_;
        return wi.normalize();
    }
    
    double pdf(Material* mat,Hitinfo const& hitinfo, Vect3 const& wi, Vect3 const& wo){
        double ndotwo = hitinfo.normal.dot(wo);
        Vect3 r = wo.neg() + hitinfo.normal * 2 * ndotwo;
        double lobe = std::pow(r.dot(wi),e);
        return lobe * (hitinfo.normal.dot(wi));
    }
    
    Vect3 eval(Material* mat,Hitinfo const& hitinfo,Vect3 const& wi,Vect3 const& wo){
        double ndotwo = hitinfo.normal.dot(wo);
        Vect3 r = wo.neg() + hitinfo.normal * 2 * ndotwo;
        double lobe = std::pow(r.dot(wi),e);
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

public:
    double e;
    double ks;
    Vect3 cs;
};

#endif /* Glossy_h */
