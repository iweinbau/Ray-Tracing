#ifndef Disney_h
#define Disney_h

#include "Material.hpp"
#include "../tracer.hpp"
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

    virtual Vect3 shade(Hitinfo const& hitinfo,World const& world,int depth){

        //********** AMBIENT COLOR ********** \\
        //set color to ambient light.
        Vect3 color;

        for(Light* l : world.lights){
            Vect3 lightDir = l->getDirection(hitinfo);
            //********* CAST SHADOW RAY ********** \\
            //cast shadow ray to check if the object is in shadow.
            Ray shadowray(hitinfo.point + Vect3(hitinfo.normal) * kEpsilon,lightDir);
            if(!l->shadow_hit(shadowray,world)){
                double ndotLightDir = hitinfo.normal.dot(lightDir);
                if(ndotLightDir > 0){
                    Vect3 df = brdf->sample(this,hitinfo,lightDir) * l->getIntensity(hitinfo);
                    color = color + df;
                }
            }
            Vect3 reflectance = brdf->Sample(this,hitinfo,hitinfo.direction.neg());
            double pdf = brdf->PDF(this,hitinfo,hitinfo.direction.neg(),reflectance);
            Ray reflectionRay = Ray(hitinfo.point + Vect3(hitinfo.normal)*kEpsilon, reflectance);
            color = color + brdf->sample(this,hitinfo,reflectance) * tr.trace(reflectionRay,world,depth-1)/pdf;
        }

        return color;
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
    Vect3 baseColor = Vect3(0.86,0.67,0.16);
    double metallic = 1;
    double subsurface = 0;
    double specular = 0;
    double roughness = 1;
    double specularTint = 1;
    double anisotropic = 0;
    double sheen = 0;
    double sheenTint = 0.5;
    double clearcoat = 0;
    double clearcoatGloss = 1;
    tracer tr;
    PrincipledBRDF* brdf;
};

#endif /* Matte_h */
