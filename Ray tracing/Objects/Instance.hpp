//
//  Instance.hpp
//  raytracer
//
//  Created by Iwein Bau on 22/03/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#ifndef Instance_hpp
#define Instance_hpp

#include "Object.hpp"
#include "../Utils/Transform.hpp"
class Instance : public Object{
public:
    Instance();
    Instance(Object* obj, Material* mat);
    ~Instance();
    bool hit(Ray const& ray, Point3& intersection, double& tmin,Normal& normal);
    Box caluclateBoundingBox();
    void translate(Vect3 const& vect);
    void scale(Vect3 const& scale);
    void rotateX(double d);
    void rotateY(double d);
    void rotateZ(double d);
private:
    Object* object;
    Transform transform;
};

#endif /* Instance_hpp */
