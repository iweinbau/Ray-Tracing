

#include "./Directional.hpp"

Directional::Directional(Vect3 direction, Vect3 color, double i):Light(color,i),direction_(direction){}
Directional::~Directional(){}

Vect3 Directional::getDirection(Hitinfo& hitinfo){
  return direction_;
}

Vect3 Directional::getIntensity(Hitinfo& hitinfo,World& world){
  return color_ * i_;
}

bool Directional::shadow_hit(Ray const& ray,World& world){
  return false;
}
