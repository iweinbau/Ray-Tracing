//
//  World.cpp
//  raytracer
//
//  Created by Iwein Bau on 25/02/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//


#include "./World.hpp"

#include "../Material/Mirror.hpp"
#include "../Material/Matte.hpp"
#include "../Material/Reflective.hpp"
#include "../Material/Matte.hpp"
#include "../Material/Emissive.hpp"
#include "../Material/Disney.hpp"



#include "../Objects/sphere.hpp"
#include "../Objects/Rectangle.hpp"
#include "../Objects/Plane.hpp"
#include "../Objects/Instance.hpp"

#include "../Light/pointLight.hpp"
#include "../Light/Directional.hpp"
#include "../Light/AreaLight.hpp"

#include "../Utils/ThinLens.hpp"


//Constructor
World::World(){}
World::~World(){
    {
        for(int i=0; i < lights.size(); i++) {
            delete(lights[i]);
            lights[i] = NULL;
        }
        lights.erase(lights.cbegin(),lights.cend());
        
        for(int i=0; i < objects.size(); i++) {
            delete(objects[i]);
            objects[i] = NULL;
        }
        objects.erase(objects.cbegin(),objects.cend());
        
        delete(camera);
        camera = NULL;
    }
}

void World::buildWorld(){
    
    //Camera setup
    //construct a camera
    Point3 lookfrom(0,0,10);
    Vect3 lookat(0,0,0);
    camera = new ThinLens(lookfrom, lookat, 90, 10, 1);
    
    // ONLY FOR indirect illumination.
    Rectangle* r = new Rectangle(Point3(-2.5,5,0),Vect3(5,0,0),Vect3(0,0,5),new Emissive(10,Vect3(1)));
    r->setShadowCast(false);

    // ONLY FOR direct illumination.
    //AreaLight* light = new AreaLight(r,Vect3(1),10);
    //add_Light(light);
    
    ambientLight = AmbientLight(0.5,Vect3(1),1);
    
    Phong* mat3 = new Phong(
                              Lambertian(0.7,Vect3(0.3,0,0)),
                              new Lambertian(0.5,Vect3(0.8,0,0)),
                              new Glossy(0.5,10000,Vect3(1,0,0)));

    Sphere* sphere = new Sphere(Point3(0, 0, 0), 1);

    Instance* s = new Instance(sphere,mat3);
    s->scale(Vect3(3));
    s->translate(Vect3(0, 0, -2));

    Matte* planem = new Matte(
                 Lambertian(0.25,Vect3(1)),
                 new Lambertian(0.5,Vect3(1)));
    Matte* planet = new Matte(
                              Lambertian(0.25,Vect3(1)),
                              new Lambertian(0.5,Vect3(1)));
    Matte* planeb = new Matte(
                 Lambertian(0.25,Vect3(1)),
                 new Lambertian(0.5,Vect3(1)));

    Matte* planel = new Matte(
                 Lambertian(0.25,Vect3(1,0,0)),
                 new Lambertian(0.5,Vect3(1,0,0)));
    Matte* planer = new Matte(
                 Lambertian(0.25,Vect3(0,1,0)),
                 new Lambertian(0.5,Vect3(0,1,0)));

    Plane* planeback = new Plane(Point3(0, 0, -5), Normal(0,0,1),planem);
    Plane* planeleft = new Plane(Point3(-5, 0, 0), Normal(1,0,0),planel);
    Plane* planeright = new Plane(Point3(5, 0, 0), Normal(-1,0,0),planer);
    Plane* planebottom = new Plane(Point3(0, -5, 0), Normal(0,1,0),planeb);
    Plane* planetop =  new Plane(Point3(0, 5, 0), Normal(0,-1,0),planet);

    add_object(s);
    add_object(r);
    add_object(planeback);
    add_object(planeleft);
    add_object(planeright);
    add_object(planebottom);
    add_object(planetop);
}
