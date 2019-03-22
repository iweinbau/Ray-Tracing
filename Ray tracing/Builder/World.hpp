//
//  World.hpp
//  Ray Tracer
//
//  Created by Iwein Bau on 25/02/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#ifndef World_h
#define World_h

#include <vector>
#include "../Utils/Vect3.hpp"
#include "../Utils/Normal.hpp"
#include "../Objects/Object.hpp"
#include "../Light/Light.hpp"

class World{
public:
    World();
    ~World();
    virtual void buildWorld();
    void add_object(Object* obj);
    void add_Light(Light* l);
    
    std::vector<Object*> objects;
    std::vector<Light*> lights;
    
};

inline void World::add_object(Object* obj){
    objects.push_back(obj);
};

inline void World::add_Light(Light* light){
    lights.push_back(light);
}
#endif /* World_h */
