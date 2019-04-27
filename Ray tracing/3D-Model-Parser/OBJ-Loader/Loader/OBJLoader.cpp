//
//  MeshLoader.c
//  OBJ-Loader
//
//  Created by Iwein Bau on 21/02/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>

#include "./MeshLoader.hpp"
#include "../../../Utils/Vect3.hpp"
#include "../Utils/Vect2.hpp"
#include "../Utils/Algorithm.hpp"

namespace MeshLoader {
    //Constructor
    OBJLoader::OBJLoader():MeshLoader(){}
    //Destructor
    OBJLoader::~OBJLoader(){};

    //OBJ Loader object.
    bool OBJLoader::loadMesh (std::string filePath){
        // If the file is not an .obj file return false
        if (filePath.substr(filePath.size() - 4, 4) != ".obj"){
            std::cout << "No .obj file found at given file location: "<<filePath << std::endl;

        }
        //Open file stream
        std::ifstream file(filePath);

        //check if file is open.
        if (!file.is_open()){
            std::cout << "File was not opened!" << std::endl;
            return false;
        }

        //Do file loading.
        std::cout << "Parsing obj-file: "<<filePath << std::endl;

        //constuct mesh data.
        bool smoothShading = false;
        std::string obj_name;
        std::vector<Vertex> vertices;
        std::vector<Vect3> Positions;
        std::vector<Vect3> Normals;
        std::vector<Vect2> UVs;

        std::vector<unsigned int> V_indices;

        //the current line
        std::string currentLine;
        //loop over each line and parse the needed data.
        while(std::getline(file, currentLine)){

            //for now we just print the line
            std::cout << currentLine << std::endl;
            
            if(algorithm::startsWith(currentLine, "s ")){
                std::vector<std::string> line_split = algorithm::split(currentLine,' ');
                if( line_split[1] == std::string("off")){
                    smoothShading = false;
                }else if(line_split[1] == std::string("1")){
                    //enalbe smooth shading;
                    smoothShading = true;
                }
            }

            //check if the line starts with v -> vertex.
            if(algorithm::startsWith(currentLine, "o ")){
                //construct new vertex position.
                std::vector<std::string> line_split = algorithm::split(currentLine,' ');

                obj_name = line_split[1];
            }

            //check if the line starts with v -> vertex.
            if(algorithm::startsWith(currentLine, "v ")){
                //construct new vertex position.
                std::vector<std::string> line_split = algorithm::split(currentLine,' ');

                float x = std::stof(line_split[1]);
                float y = std::stof(line_split[2]);
                float z = std::stof(line_split[3]);
                Vect3 pos = Vect3(x,y,z);
                Positions.push_back(pos);
            }

            //check if the line starts with vt -> vertex uv.
            if(algorithm::startsWith(currentLine, "vt ")){
                //construct new vertex uv.
                std::vector<std::string> line_split = algorithm::split(currentLine,' ');

                float u = std::stof(line_split[1]);
                float v = std::stof(line_split[2]);
                Vect2 uv = Vect2(u,v);
                UVs.push_back(uv);
            }

            //check if the line starts with vn -> vertex normals.
            if(algorithm::startsWith(currentLine, "vn ")){
                //construct new vertex normal.
                std::vector<std::string> line_split = algorithm::split(currentLine,' ');

                float x = std::stof(line_split[1]);
                float y = std::stof(line_split[2]);
                float z = std::stof(line_split[3]);
                Vect3 normal = Vect3(x,y,z);
                Normals.push_back(normal);
            }

            //check if the line starts with f -> constuct faces.
            if(algorithm::startsWith(currentLine, "f ")){
                //construct new vertex position.

                std::vector<std::string> line_split = algorithm::split(currentLine,' ');

                //@NOTE: this only works when mesh is already triangulated.
                //Parse all vertices.
                std::vector<std::string> vertex1 = algorithm::split(line_split[1],'/');
                std::vector<std::string> vertex2 = algorithm::split(line_split[2],'/');
                std::vector<std::string> vertex3 = algorithm::split(line_split[3],'/');

                //check if T exist.
                if(vertex1[1] == ""){
                    //NO Uv
                    //V -> index in the positions array.
                    //N -> index in the normals array.

                    //VERTEX 1
                    Vect3 position = Positions[std::stoi(vertex1[0])-1];
                    Vect3 normal = Normals[std::stoi(vertex1[2])-1];

                    Vertex v1(position,normal);
                    vertices.push_back(v1);

                    //VERTEX 2
                    position = Positions[std::stoi(vertex2[0])-1];
                    normal = Normals[std::stoi(vertex2[2])-1];

                    Vertex v2(position,normal);
                    vertices.push_back(v2);

                    //VERTEX 3
                    position = Positions[std::stoi(vertex3[0])-1];
                    normal = Normals[std::stoi(vertex3[2])-1];

                    Vertex v3(position,normal);
                    vertices.push_back(v3);

                    //Add to Indices array.
                    //calculate the index number
                    //The 3 comes from 3 vertices per face.
                    unsigned int index = vertices.size() - 3;
                    V_indices.push_back(index);
                    V_indices.push_back(index+1);
                    V_indices.push_back(index+2);

                }else if (vertex1[1] != ""){
                    //We have UV
                    //V -> index in the positions array.
                    //T -> index of UV
                    //N -> index in the normals array.

                    //VERTEX 1
                    Vect3 position = Positions[std::stoi(vertex1[0])-1];
                    Vect2 uv = UVs[std::stoi(vertex1[1])-1];
                    Vect3 normal = Normals[std::stoi(vertex1[2])-1];

                    Vertex v1(position,normal,uv);
                    vertices.push_back(v1);

                    //VERTEX 2
                    position = Positions[std::stoi(vertex2[0])-1];
                    uv = UVs[std::stoi(vertex2[1])-1];
                    normal = Normals[std::stoi(vertex2[2])-1];

                    Vertex v2(position,normal,uv);
                    vertices.push_back(v2);

                    //VERTEX 3
                    position = Positions[std::stoi(vertex3[0])-1];
                    uv = UVs[std::stoi(vertex3[1])-1];
                    normal = Normals[std::stoi(vertex3[2])-1];

                    Vertex v3(position,normal,uv);
                    vertices.push_back(v3);

                    //Add to Indices array.
                    //calculate the index number
                    //The 3 comes from 3 vertices per face.
                    unsigned int index = vertices.size() - 3;
                    V_indices.push_back(index);
                    V_indices.push_back(index+1);
                    V_indices.push_back(index+2);
                }

                //We can check here in which format. V/T/N, V//N, V//, ...
                //For now we ignore this and use V//N.
            }
        }

        //close stream
        file.close();

        Positions.clear();
        Normals.clear();
        UVs.clear();

        //reorder the arrays so the coresponding index match the position,uv and normal.
        for (Vertex v: vertices) {
            Positions.push_back(v.getPosition());
            Normals.push_back(v.getNormal());
            UVs.push_back(v.getUV());
        }

        //Load mesh data.
        _mesh = Mesh(smoothShading,obj_name, Positions, Normals, UVs, V_indices);

        //return true, succes.
        return true;
    }

}
