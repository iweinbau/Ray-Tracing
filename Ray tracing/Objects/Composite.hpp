//
//  Composite.hpp
//  raytracer
//
//  Created by Iwein Bau on 29/04/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#ifndef Composite_hpp
#define Composite_hpp

#include "Object.hpp"
#include <vector>

class Normal;

class Composite: public Object{
public:
    Composite();
    Composite(Material* shader);
    ~Composite();
    Box caluclateBoundingBox();
    bool hit(Ray const& ray, Point3& intersection, double& tmin,Normal& normal);
    void add_object(Object* object);
public:
    std::vector<Object*> objects;
};

inline void Composite::add_object(Object* object){
    objects.push_back(object);
}

#endif /* Composite_hpp */
