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
#include <memory>

class Normal;

class Composite: public Object{
public:
    Composite();
    Composite(Material* shader);
    ~Composite();
    Box caluclateBoundingBox();
    bool hit(Ray const& ray, Point3& intersection, double& tmin,Normal& normal);
    void add_object(std::shared_ptr<Object> const& object);
public:
    std::vector<std::shared_ptr<Object>> objects;
};

inline void Composite::add_object(std::shared_ptr<Object> const& object){
    objects.push_back(object);
}

#endif /* Composite_hpp */
