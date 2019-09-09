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
    /**
     *  Default constructor, create empty mesh object.
     */
    Mesh();
    
    /**
     *  Constructor, create new mesh object from the given name, position, normals, uv, indices.
     *  @param name The name of the mesh.
     *  @param positions vector<Vect3> represent the positions of all vertices in 3D space.
     *  @param normals vector<Vect3> represent the normals of all vertices in 3D space.
     *  @param UVs vector<Vect2> represent the uv of all vertices.
     *  @param indices vector<usigned int> represent the order of how vertices are connected.
     *
     */
    Mesh(bool smoothShading,std::string const& name,
               std::vector<Vect3> const& positions,
               std::vector<Vect3> const& normals,
               std::vector<Vect2> const& UVs,
               std::vector<unsigned int> const& indices);

    /**
     *  Default destructor.
     */
    ~Mesh(){

    }

public:
    /**
     *  If mesh is smooth shaded? This will smooth surface normals.
     */
    bool smoothShading;
    std::string _name;
    std::vector<Vect3> _positions;
    std::vector<Vect3> _normals;
    std::vector<Vect2> _UVs;
    std::vector<unsigned int> _indices;
};
#endif /* Mesh_h */
