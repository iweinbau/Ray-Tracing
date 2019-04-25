//
//  Mesh.hpp
//  OBJ-Loader
//
//  Created by Iwein Bau on 21/02/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#ifndef Mesh_h
#define Mesh_h

#include <iostream>
#include <vector>

#include "../Utils/Vect2.hpp"
#include "../../../Utils/Vect3.hpp"

class Mesh {
public:
    // Constructor
    Mesh();
    Mesh(std::string const& name,
               std::vector<Vect3> const& positions,
               std::vector<Vect3> const& normals,
               std::vector<Vect2> const& UVs,
               std::vector<unsigned int> const& indices);

    // Destructor.
    ~Mesh(){

    }

public:
    std::string _name;
    std::vector<Vect3> _positions;
    std::vector<Vect3> _normals;
    std::vector<Vect2> _UVs;
    std::vector<unsigned int> _indices;
};
#endif /* Mesh_h */
