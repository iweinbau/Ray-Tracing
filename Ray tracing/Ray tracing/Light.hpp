//
//  Light.hpp
//  Ray-tracer
//
//  Created by Iwein Bau on 17/12/2018.
//  Copyright © 2018 Iwein Bau. All rights reserved.
//

#ifndef Light_h
#define Light_h

#include "vector3f.hpp"

class Light {
public:
    Light(Vect3 diffuse, Vect3 specular, Vect3 position):
    diffuse_(diffuse),
    specular_(specular),
    position_(position)
    {}
    Vect3 getPosition() {
        return position_;
    }
    Vect3 getDiffuse() {
        return diffuse_;
    }
    Vect3 getSpecular() {
        return specular_;
    }
private:
    Vect3 specular_;
    Vect3 diffuse_;
    Vect3 position_;
    
};

#endif /* Light_h */
