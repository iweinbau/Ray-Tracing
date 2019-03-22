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
#include "../Utils/Matrix.hpp"
#include "../Utils/Normal.hpp"
class Instance : public Object{
public:
    Instance();
    Instance(Object* obj, Material* mat);
    ~Instance();
    bool hit(Ray const& ray, Point3& intersection, double& tmin,Normal& normal);
    void translate(Vect3 const& vect);
    void scale(Vect3 const& scale);
private:
    Object* object;
    Matrix4 invTransform;
};

#endif /* Instance_hpp */
