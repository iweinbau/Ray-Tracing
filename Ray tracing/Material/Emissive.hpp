//
//  Emissive.hpp
//  raytracer
//
//  Created by Iwein Bau on 07/06/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#ifndef Emissive_hpp
#define Emissive_hpp

#include "./Material.hpp"

class Emissive: public Material{
public:
    Emissive(double ls, Vect3 cl):ls(ls),cl(cl)
    {}
    
    Emissive(Emissive const& mat):ls(mat.ls),cl(mat.cl)
    {}
    
    ~Emissive()
    {}
    
    Material* clone() {
        return new Emissive(*this);
    }
    
    Emissive& operator= (Emissive const& mat)
    {
        if(this == &mat)
            return (*this);
        ls = mat.ls;
        cl = mat.cl;
        return (*this);
    }
    
    virtual Vect3 direct_shade(Hitinfo& hitinfo,World& world,int depth);
    virtual Vect3 indirect_shade(Hitinfo& hitinfo,World& world,int depth);
    
private:
    double ls;
    Vect3 cl;
    
};

#endif /* Emissive_hpp */
