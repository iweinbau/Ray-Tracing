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

class Grid{
public:
    Grid();
    ~Grid();
    bool hit(Ray const& ray, Point3& intersection, double& tmin,Normal& normal);
    void add_object(Object* object);
    void constructCells();
private:
    int Mx,My,Mz;
    std::vector<Object*> objects;
    std::vector<Object*> cells;
};

#endif /* Grid_hpp */
