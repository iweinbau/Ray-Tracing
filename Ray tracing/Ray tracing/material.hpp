//
//  material.hpp
//  Ray-tracer
//
//  Created by Iwein Bau on 16/12/2018.
//  Copyright © 2018 Iwein Bau. All rights reserved.
//

#ifndef material_h
#define material_h

class material {
public:
    material()
    {}
    
    material(Vect3 ambient, Vect3 diffuse,Vect3 specular, double shininess):
    diffuseColor(diffuse),
    ambientColor(ambient),
    specularColor(specular),
    shininess(shininess),
    reflection(0),
    reflective(false)
    {}
    
    material(Vect3 ambient, Vect3 diffuse,Vect3 specular, double shininess, double reflection):
    diffuseColor(diffuse),
    ambientColor(ambient),
    specularColor(specular),
    shininess(shininess),
    reflection(reflection){
        if(reflection >= 0){
            this->reflective = true;
            this->reflection = reflection;
        }else{
            this->reflective = false;
            this->reflection = 0;
        }
    }

    material(material const& mat)
    {
        diffuseColor = mat.diffuseColor;
        ambientColor = mat.ambientColor;
        specularColor = mat.specularColor;
        shininess = mat.shininess;
        reflection = mat.reflection;
        reflective = mat.reflective;
    }
    
    ~material()
    {}
    
    material& operator= (material const& mat)
    {
        if( this == &mat)
            return (*this);
        
        diffuseColor = mat.diffuseColor;
        ambientColor = mat.ambientColor;
        specularColor = mat.specularColor;
        shininess = mat.shininess;
        reflection = mat.reflection;
        reflective = mat.reflective;
        
        return (*this);
    }
    
    bool reflective;
    double reflection;
    Vect3 diffuseColor;
    double shininess;
    Vect3 specularColor;
    Vect3 ambientColor;
};

#endif /* material_h */
