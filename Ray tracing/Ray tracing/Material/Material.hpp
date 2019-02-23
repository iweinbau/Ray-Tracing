//
//  Material.hpp
//  Ray-tracer
//
//  Created by Iwein Bau on 17/12/2018.
//  Copyright © 2018 Iwein Bau. All rights reserved.
//

#ifndef Material_h
#define Material_h

#include "../Hitinfo.hpp"
#include "../Light/Light.hpp"
#include <iostream>
#include <vector>

class Material{
public:
    Material()
    {}
    
    Material(Material const& mat)
    {}
    
    ~Material()
    {}
    
    Material& operator= (Material const& mat)
    {
        if(this == &mat)
            return (*this);
        
        return (*this);
    }
    virtual Vect3 shade(Hitinfo const& hitinfo,std::vector<Object*> const& objects,std::vector<Light*> const& lights,int depth) = 0;
    
};

#endif /* Material_h */