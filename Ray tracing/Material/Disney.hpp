#ifndef Disney_h
#define Disney_h

#include "Material.hpp"
#include "../Utils/GlobalTracer.hpp"
#include "../Light/Light.hpp"
#include "../BRDF/Principled_BRDF.hpp"

class Disney: public Material{
public:
    Disney():Material(),brdf(new PrincipledBRDF())
    {}

    Disney(double baseColor,
          double metallic,
          double subsurface,
          double specular,
          double roughness,
          double specularTint,
          double anisotropic,
          double sheen,
          double sheenTint,
          double cleaercoat,
          double clearcoatGloss):
    Material(),
    brdf(new PrincipledBRDF())
    {}

    Disney(Disney const& d):
    Material(),
    brdf(d.brdf)
    {}

    ~Disney()
    {}

    Vect3 direct_shade(Hitinfo& hitinfo,World& world,int depth){
        return Vect3();
    }
    
    Vect3 indirect_shade(Hitinfo& hitinfo,World& world,int depth){
        //1 Sample point
        Vect3 wi = brdf->sample(this, hitinfo, hitinfo.direction.neg());
        Ray r(hitinfo.point + wi * kEpsilon, wi);
        //2 calculate pdf
        double pdf = brdf->pdf(this, hitinfo, wi, hitinfo.direction.neg());
        //3 evaluate brdf
        Vect3 f = brdf->eval(this, hitinfo,wi,hitinfo.direction.neg());
        
        return f * tr.trace(r, world, depth +1) * hitinfo.normal.dot(wi)/ pdf;
    }

    Disney& operator= (Disney const& d)
    {
        if(this == &d)
            return (*this);

        Material::operator=(d);

        brdf = d.brdf;

        return (*this);
    }
  public:
    Vect3 baseColor = Vect3(1);
    double metallic = 0;
    double subsurface = 0;
    double specular = 0.5;
    double roughness = 0;
    double specularTint = 0;
    double anisotropic = 0;
    double sheen = 0;
    double sheenTint = 0;
    double clearcoat = 0;
    double clearcoatGloss = 0;
    GlobalTracer tr;
    PrincipledBRDF* brdf;
};

#endif /* Matte_h */
