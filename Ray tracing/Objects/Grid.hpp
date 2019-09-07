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
#include "../3D-Model-Parser/OBJ-Loader/Mesh/Mesh.hpp"
#include "Box.hpp"
#include "Composite.hpp"

class Grid:public Composite{
public:
    Grid();
    Grid(Mesh const& mesh,Material* material);
    Grid(Grid const& grid);
    ~Grid();
    Object* clone();
    bool hit(Ray const& ray, Point3& intersection, double& tmin,Normal& normal);
    Box caluclateBoundingBox();
    void constructCells();
private:
    Box bbox;
    int Mx,My,Mz;
    int density=5;
    std::vector<Composite*> cells;
};

#endif /* Grid_hpp */
