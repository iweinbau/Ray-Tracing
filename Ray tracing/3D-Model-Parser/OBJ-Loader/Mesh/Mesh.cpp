//
//  Mesh.cpp
//  OBJ-Loader
//
//  Created by Iwein Bau on 22/02/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#include "Mesh.hpp"

Mesh::Mesh(){};
Mesh::Mesh(bool smoothShading,std::string const& name,
           std::vector<Vect3> const& positions,
           std::vector<Vect3> const& normals,
           std::vector<Vect2> const& UVs,
           std::vector<unsigned int> const& indices):
            smoothShading(smoothShading),
            _name(name),
            _positions(positions),
            _normals(normals),
            _UVs(UVs),
            _indices(indices){};
