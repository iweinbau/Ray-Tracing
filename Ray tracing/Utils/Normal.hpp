//
//  Normal.hpp
//  Ray Tracer
//
//  Created by Iwein Bau on 22/03/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#ifndef Normal_h
#define Normal_h

#include "Vect3.hpp"

class Point3;
class Vect3;

class Normal: public Vect3{
public:
    Normal();
    
    Normal(double x, double y, double z);
    
    Normal(Normal const &v);
    
    Normal(Point3 const& p);
    
    Normal(Vect3 const& v);

    
    ~Normal();
    Normal& operator= (Normal const& v);
};


#endif /* Normal_h */
