#ifndef PrincipledSpecular_h
#define PrincipledSpecular_h

#include "BRDF.hpp"
#include "../Utils/Math.hpp"
#include "../Utils/Constants.hpp"


class Disney;

class PrincipledBRDF:public BRDF{
public:
    PrincipledBRDF();

    ~PrincipledBRDF();

    double pdf(Disney* mat,Hitinfo const& hitinfo, Vect3 const& wi, Vect3 const& wo);

    Vect3 sample(Disney* mat,Hitinfo const& hitinfo, Vect3 const& wo);

    Vect3 eval(Disney* mat,Hitinfo const& hitinfo,Vect3 const& wi,Vect3 const& wo);
    
private:
    double fresnel(double cosT);
    double GTR1(double cosT,double a);
    double GTR2(double cosT,double a);
    double GGX(double cosT,double a);
    double k(double a, double y);
    PrincipledBRDF& operator= (PrincipledBRDF const& d);
};

inline double PrincipledBRDF::fresnel(double cosT){
    double v = clamp(1-cosT,0,1);
    double v2 = v *v;
    return v2 * v2 * v;
}

inline double PrincipledBRDF::GTR1(double cosT,double a){
    if(a >= 1) return 1/PI;
    double t = (1+(a*a-1)*cosT*cosT);
    return (a*a-1.0f) / (PI*log(a*a)*t);
}

inline double PrincipledBRDF::GTR2(double cosT,double a){
    double t = (1+(a*a-1)*cosT*cosT);
    return (a*a) / (PI*t*t);
}

inline double PrincipledBRDF::GGX(double cosT, double a){
    double a2 = a*a;
    double b = cosT*cosT;
    return 1.0/ (cosT + sqrt(a2 + b - a2*b));
}
#endif /* Specular_h */

