//
//  ThinLens.hpp
//  Ray-tracing
//
//  Created by Iwein Bau on 17/08/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#ifndef ThinLens_hpp
#define ThinLens_hpp

#include "./Camera.hpp"
#include "../Sampler/Sampler.hpp"
#include "../3D-Model-Parser/OBJ-Loader/Utils/Vect2.hpp"

class ThinLens : public Camera {
public:
    ThinLens(Point3 lookfrom, Vect3 lookat, double fovy, double lensRadius, double focal);
    ThinLens();
    ~ThinLens();
    virtual Ray constructRay(int i, int j);


private:
    double lensRadius;
    double focalDistance;
};

#endif /* ThinLens_hpp */
