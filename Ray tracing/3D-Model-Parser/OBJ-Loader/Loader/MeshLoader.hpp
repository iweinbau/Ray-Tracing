//
//  MeshLoader.hpp
//  OBJ-Loader
//
//  Created by Iwein Bau on 21/02/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#ifndef MeshLoader_h
#define MeshLoader_h

#include <iostream>
#include "../Mesh/Mesh.hpp"

namespace MeshLoader {
    class MeshLoader {
    public:
        MeshLoader(){};
        ~MeshLoader(){};
        Mesh getLoadedMesh(){
            return _mesh;
        }
        virtual bool loadMesh(std::string filePath) = 0;
    protected:
        Mesh _mesh;
    };

    class OBJLoader: public MeshLoader{
    public:
        OBJLoader();
        ~OBJLoader();
        bool loadMesh(std::string filePath);
    private:
    };

    class Vertex{
    public:
        Vertex():
        _pos(),_normal(),_uv(){}
        
        Vertex(Vect3 pos):
        _pos(pos),_normal(),_uv(){}

        Vertex(Vect3 pos, Vect3 normal, Vect2 uv):
        _pos(pos),
        _normal(normal),
        _uv(uv){}

        Vertex(Vect3 pos,Vect3 normal):
        _pos(pos),_normal(normal),_uv(){}

        ~Vertex(){}

        Vect3 getPosition(){
            return _pos;
        }
        Vect3 getNormal(){
            return _normal;
        }
        Vect2 getUV(){
            return _uv;
        }

    private:
        int _index;
        Vect3 _pos;
        Vect3 _normal;
        Vect2 _uv;

    };
}
#endif /* MeshLoader_h */
