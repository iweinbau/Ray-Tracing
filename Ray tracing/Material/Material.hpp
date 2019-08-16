//
//  Material.hpp
//  Ray-tracer
//
//  Created by Iwein Bau on 17/12/2018.
//  Copyright © 2018 Iwein Bau. All rights reserved.
//

#ifndef Material_h
#define Material_h

#include "../Utils/Hitinfo.hpp"
#include "../Builder/World.hpp"

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
    
    /**
     *  Calculate the contribution of the material using direct light sampling
     *  @param hitinfo HintInfo of current node in the path.
     *  @param world World info.
     *  @param depth recursion depth
     *  @return Vect3
     */
    virtual Vect3 direct_shade(Hitinfo& hitinfo,World& world,int depth) = 0;
    
    /**
     *  Calculate the contribution of the material using indirect light sampling
     *  @param hitinfo HintInfo of current node in the path.
     *  @param world World info.
     *  @param depth recursion depth
     *  @return Vect3
     */
    virtual Vect3 indirect_shade(Hitinfo& hitinfo,World& world,int depth){
        return Vect3();
    };

};

#endif /* Material_h */
