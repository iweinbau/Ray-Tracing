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
        r = hitinfo.direction - ( hitinfo.normal * 2 * hitinfo.direction.dot(hitinfo.normal));
        return cs * ks;
    }
    
    //glossy reflection.
    Vect3 sample_(Hitinfo const& hitinfo,Vect3& out){
        
        Vect3 r = hitinfo.direction - ( hitinfo.normal * 2 * hitinfo.direction.dot(hitinfo.normal));
        
        Vect3 w = r;
        Vect3 u = Vect3(0.00424, 1, 0.00764).cross(w);
        u.normalize();
        Vect3 v = u.cross(w);
        
        std::random_device rd;  //Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
        std::uniform_real_distribution<> dis(0.0, 1.0);
        
        double espilon1 = dis(gen);
        double espilon2 = dis(gen);

        double uu = - e/2 + espilon1;
        double vv = -e/2 + espilon2;
        
        out = r + u * uu + v * vv;// reflected ray direction
        
        return cs * ks;
        
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
    double ks;
    Vect3 cs;
};

#endif /* Glossy_h */
