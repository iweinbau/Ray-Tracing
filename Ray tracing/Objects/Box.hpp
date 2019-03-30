#ifndef Box_h
#define Box_h
#include "../Utils/ray.hpp"
#include "../Utils/Point3.hpp"

class Box {
private:
    Point3 p1,p2;
public:
  Box(const Point3& p1, const Point3& p2);
  Box();
  ~Box();
  bool hit(Ray const& ray);
    Point3 * getVertices(Point3 v[8]);
};
#endif
