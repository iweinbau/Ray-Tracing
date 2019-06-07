//
//  Emisseve.cpp
//  raytracer
//
//  Created by Iwein Bau on 07/06/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#include "Emissive.hpp"

Vect3 Emissive::direct_shade(Hitinfo& hitinfo,World& world,int depth){
    //Only send light at one side of the surface.
    if(-hitinfo.normal.dot(hitinfo.direction) > 0){
        return ls*cl;
    }else{
        return Vect3();
    }
}
Vect3 Emissive::indirect_shade(Hitinfo& hitinfo,World& world,int depth){
    //if depth == return black els we could count the light source twice.
    if(depth == 1){
        return Vect3();
    }
    
    //Only send light at one side of the surface.
    if(-hitinfo.normal.dot(hitinfo.direction) > 0){
        return ls*cl;
    }else{
        return Vect3();
    }
}
