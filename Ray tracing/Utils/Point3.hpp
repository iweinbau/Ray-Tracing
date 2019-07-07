//
//  Point3.hpp
//  Ray Tracer
//
//  Created by Iwein Bau on 22/03/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#ifndef Point3_h
#define Point3_h

#include "Vect3.hpp"

class Point3: public Vect3{
public:
    Point3();

    Point3(Vect3);
    
    Point3(double x, double y, double z);

    Point3(Point3 const &v);

    ~Point3();

    Point3& operator= (Point3 const& v);
};

#endif /* Point3_h */
