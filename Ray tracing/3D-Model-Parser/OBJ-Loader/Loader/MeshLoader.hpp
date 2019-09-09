//
//  Mesh loader base class for loading 3D models.
//  Implement the loadMesh function for new file types.
//  When mesh is loaded you can get it using getLoadedMesh().
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
        /**
         *  Constructor create new Mesh loader instance.
         */
        MeshLoader(){};
        
        /**
         *  Destructor.
         */
        ~MeshLoader(){};
        
        /**
         *  get the current loaded mesh, first you need to call loadMesh.
         *  @return Mesh the loaded mesh.
         */
        Mesh getLoadedMesh(){
            return _mesh;
        }
        
        /**
         *  Load 3D model from file in to a Mesh object.
         *  @param filePath the file path of the model you want to load.
         *  @return bool true if object is loaded, false otherwise.
         */
        virtual bool loadMesh(std::string filePath) = 0;
        
    protected:
        /**
         *  Loaded mesh.
         */
        Mesh _mesh;
    };
    
    /**
     *  Implementation of MeshLoader, this can parse and load .obj files.
     */
    class OBJLoader: public MeshLoader{
    public:
        /**
         *  Constructor create new Mesh loader instance.
         */
        OBJLoader();
        
        /**
         *  Destructor.
         */
        ~OBJLoader();
        
        /**
         *  Load 3D model from .obj file in to a Mesh object.
         *  @param filePath the obj file path of the model you want to load.
         *  @return bool true if object is loaded, false otherwise.
         */
        bool loadMesh(std::string filePath);
    };

    /**
     *  Helper data structure for loading 3D models. represent a single vertex
     *  of the 3D model at a specific position with corresponding normal and uv.
     */
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
