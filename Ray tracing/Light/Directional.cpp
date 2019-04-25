

#include "./Directional.hpp"

Directional::Directional(Vect3 direction, Vect3 color, double i):Light(color,i),direction_(direction){}
Directional::~Directional(){}

Vect3 Directional::getDirection(Hitinfo const& hitinfo){
  return direction_;
}

Vect3 Directional::getIntensity(Hitinfo const& hitinfo){
  return color_ * i_;
}

bool Directional::shadow_hit(Ray const& ray,World const& world){
  return false;
}
