
#ifndef Directional_h
#define Directional_h

#include "./Light.hpp"

class Directional: public Light {
public:
  Directional(Vect3 direction, Vect3 color, double i);
  ~Directional();

  Vect3 getDirection(Hitinfo& hitinfo);

  Vect3 getIntensity(Hitinfo& hitinfo,World& world);

  bool shadow_hit(Ray const& ray,World& world);
private:
  Vect3 direction_;
};

#endif
