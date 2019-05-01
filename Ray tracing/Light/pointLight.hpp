//
//  pointLight.hpp
//  Ray-tracer
//
//  Created by Iwein Bau on 18/12/2018.
//  Copyright © 2018 Iwein Bau. All rights reserved.
//

#ifndef pointLight_h
#define pointLight_h

#include "Light.hpp"

#define PI 3.14159265


class PointLight : public Light{
public:
    PointLight(Vect3 color, Vect3 position,double i):
    Light(color,i),position_(position)
    {}

    PointLight(PointLight const& l):
    Light(l)
    {}

    PointLight& operator= (PointLight const& l){
        if(this == &l)
            return (*this);

        Light::operator=(l);
        return (*this);
    }

    Vect3 getPosition() {
        return position_;
    }

    Vect3 virtual getDirection(Hitinfo const& hitinfo){
      return (position_ - hitinfo.point).normalize();
    }

    Vect3 virtual getIntensity(Hitinfo const& hitinfo){
        double distance = (position_ - hitinfo.point).length();
        double attenuation = 1 / (distance * distance);
        return (color_ * i_ * attenuation);
    }

    bool virtual shadow_hit(Ray const& ray,World const& world){
      double t;
      double maxt = (position_ - ray.origin_).length();
      Point3 intersection;
      Normal normal;
      for(Object* obj : world.objects){
          if (obj->hit(ray,intersection, t,normal)) {
              if(t < maxt){
                  return true;
              }
          }
      }
      return false;
    }

  private:
      Vect3 position_;
};
#endif /* pointLight_h */
