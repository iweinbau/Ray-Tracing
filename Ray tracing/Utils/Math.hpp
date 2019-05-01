//
//  Math.hpp
//  Ray Tracer
//
//  Created by Iwein Bau on 29/04/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#ifndef Math_h
#define Math_h

#include <type_traits>

inline double clamp(double value,double min, double max){
    return ( value<min? min :(value>max ? max:value));
}

#endif /* Math_h */
