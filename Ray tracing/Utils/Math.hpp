//
//  Math.hpp
//  Ray Tracer
//
//  Created by Iwein Bau on 29/04/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#ifndef Math_h
#define Math_h

inline double clamp(double value,double min, double max){
    return ( value<min? min :(value>max ? max:value));
}

//lineair interpolate between a and b with distance t
inline double lerp(double t, double a, double b){
    return (1-t)*a + t*b;
}

inline Vect3 lerp(Vect3 t, Vect3 a, Vect3 b){
    return (Vect3(1)-t)*a + t*b;
}
#endif /* Math_h */
