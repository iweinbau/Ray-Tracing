//
//  Grid.hpp
//  raytracer
//
//  Created by Iwein Bau on 28/03/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#ifndef Grid_hpp
#define Grid_hpp

#include <vector>
#include "Object.hpp"
#include "Box.hpp"
#include "Composite.hpp"

class Grid:public Object{
public:
    Grid();
    ~Grid();
    bool hit(Ray const& ray, Point3& intersection, double& tmin,Normal& normal);
    Box caluclateBoundingBox();
    void add_object(Object* object);
    void constructCells();
private:
    Box bbox;
    int Mx,My,Mz;
    int density=5;
    std::vector<Object*> objects;
    std::vector<Composite*> cells;
};

#endif /* Grid_hpp */
