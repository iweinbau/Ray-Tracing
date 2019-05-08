#ifndef PrincipledSpecular_h
#define PrincipledSpecular_h

#include "BRDF.hpp"
#include "../Utils/Math.hpp"

class Disney;

class PrincipledBRDF:public BRDF{
public:
    PrincipledBRDF();

    ~PrincipledBRDF();

    double PDF(Disney* mat,Hitinfo const& hitinfo, Vect3 const& v, Vect3 const& ld);

    Vect3 Sample(Disney* mat,Hitinfo const& hitinfo, Vect3 const& i);

    Vect3 sample(Disney* mat,Hitinfo const& hitinfo,Vect3 const& ld);

    Vect3 lerp(Vect3 a, Vect3 b, double t);

    double lerp(double a, double b, double t);


    double GTR1(double u, double a);

    double GTR2(double u, double a);

    double smithG_GGX(double u, double alphaG);

    double Schlick_fresnel(double u);

    Vect3 color();

    PrincipledBRDF& operator= (PrincipledBRDF const& d);
};

#endif /* Specular_h */
