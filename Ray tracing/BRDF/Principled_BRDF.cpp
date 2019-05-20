#include "../Utils/Constants.hpp"
#include "Principled_BRDF.hpp"
#include "../Material/Disney.hpp"
#include <random>

PrincipledBRDF::PrincipledBRDF():BRDF()
{}

PrincipledBRDF::~PrincipledBRDF()
{}

double PrincipledBRDF::PDF(Disney* mat,Hitinfo const& hitinfo, Vect3 const& v, Vect3 const& ld){
  Vect3 n = hitinfo.normal;;
  Vect3 V = v;
  Vect3 L = ld;

  double specularAlpha = std::max(0.001, mat->roughness);
  double clearcoatAlpha = lerp(0.1, 0.001, mat->clearcoatGloss);

  double diffuseRatio = 0.5 * (1 - mat->metallic);
  double specularRatio = 1 - diffuseRatio;

  Vect3 half = (L+V).normalize();

  double cosTheta = abs(half.dot(n));
  double pdfGTR2 = GTR2(cosTheta, specularAlpha) * cosTheta;
  double pdfGTR1 = GTR1(cosTheta, clearcoatAlpha) * cosTheta;

  // calculate diffuse and specular pdfs and mix ratio
  double ratio = 1.0 / (1.0 + mat->clearcoat);
  double pdfSpec = lerp(pdfGTR1, pdfGTR2, ratio) / (4.0 * abs(L.dot(half)));
  double pdfDiff = abs(L.dot(n))* (1.0 / PI);

  // weight pdfs according to ratios
  return  diffuseRatio * pdfDiff + specularRatio * pdfSpec;
}

Vect3 PrincipledBRDF::Sample(Disney* mat,Hitinfo const& hitinfo, Vect3 const& i)
{
  Vect3 V = i;
  Vect3 w = hitinfo.normal;
  Vect3 u = Vect3(0.00424, 1, 0.00764).cross(w);
  u.normalize();
  Vect3 v = u.cross(w);

  std::random_device rd;  //Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
  std::uniform_real_distribution<> dis(0.0, 1.0);

  //From raytracing from the ground up.
  double x = dis(gen);
  double y = dis(gen);

  double phi = x * 2.0f * PI;

  double a = std::max(0.001, mat->roughness);

  double cos_theta = std::sqrt((1.0f - y) / (1.0f + (a*a-1.0f) *y));
  double sin_theta = std::sqrt(1.0f - (cos_theta * cos_theta));
  double sin_phi = std::sin(phi);
  double cos_phi = std::cos(phi);

  double pu = sin_theta * cos_phi;
  double pv = sin_theta * sin_phi;
  double pw = cos_theta;

  Vect3 out = u * pu + v * pv + w * pw;

  if (hitinfo.normal.dot(out) < 0.0)                         // reflected ray is below tangent plane
      out = u * - pu + v * -pv + w * pw;

  return 2.0f*V.dot(out)*out - V;
}


Vect3 PrincipledBRDF::sample(Disney* mat,Hitinfo const& hitinfo,Vect3 const& ld){
    Vect3 N = hitinfo.normal;
    Vect3 V = hitinfo.direction.neg();
    Vect3 L = ld;
    Vect3 H = (L + V).normalize();

    double NdotL = N.dot(L);
    double NdotV = N.dot(V);
    double LdotH = L.dot(H);
    double NdotH = N.dot(H);

    if (NdotL <= 0.0 || NdotV <= 0.0) return Vect3(0.0);

    //base color;
    Vect3 Cd = mat->baseColor;
    double Cdlum = 0.3*Cd.x_ + 0.6*Cd.y_ + 0.1*Cd.z_; // luminance approx.

    Vect3 Ctint = Cdlum > 0.0 ? Cd / Cdlum : Vect3(1.0); // normalize lum. to isolate hue+sat
    Vect3 Cspec0 = lerp(mat->specular*.08*lerp(Vect3(1.0f), Ctint, mat->specularTint), Cd, mat->metallic);
    Vect3 Csheen = lerp(Vect3(1.0), Ctint, mat->sheenTint);

    Cspec0.print();

    double FL = Schlick_fresnel(NdotL), FV = Schlick_fresnel(NdotV);
    double Fd90 = 0.5 + 2.0 * LdotH * LdotH * mat->roughness;
    double Fd = lerp(1.0,Fd90,FL) * lerp(1.0,Fd90,FV);

    double Fss90 = LdotH*LdotH*mat->roughness;
    double Fss = lerp(1.0, Fss90, FL) * lerp(1.0, Fss90, FV);
    double ss = 1.25 * (Fss * (1.0 / (NdotL + NdotV) - 0.5) + 0.5);

    double a = std::max(0.001, mat->roughness);

    double Ds = GTR2(NdotH, a);
    double FH = Schlick_fresnel(LdotH);
    Vect3 Fs = lerp(Cspec0, Vect3(1), FH);
    double roughg = a;
    double Gs = smithG_GGX(NdotL, roughg) * smithG_GGX(NdotV, roughg);

    // sheen
    Vect3 Fsheen = FH * mat->sheen * Csheen;

    // clearcoat (ior = 1.5 -> F0 = 0.04)
    double Dr = GTR1(NdotH, lerp(0.1, 0.001, mat->clearcoatGloss));
    double Fr = lerp(0.04, 1.0, FH);
    double Gr = smithG_GGX(NdotL, 0.25) * smithG_GGX(NdotV, 0.25);

    Vect3 factor = ((1.0 / PI) * lerp(Fd, ss, mat->subsurface)*Cd + Fsheen) * (1.0 - mat->metallic)
      + Gs*Fs*Ds + 0.25*mat->clearcoat*Gr*Fr*Dr;

  return factor;
}

Vect3 PrincipledBRDF::lerp(Vect3 a, Vect3 b, double t){
  return a + (b-a)*t;
}

double PrincipledBRDF::lerp(double a, double b, double t){
  return a + (b-a) * t;
}


double PrincipledBRDF::GTR1(double u, double a)
{
    if (a >= 1.0) return (1.0/ PI);
    double a2 = a*a;
    double t = 1.0 + (a2-1.0)*u*u;
    return (a2-1.0) / (PI*std::log(a2)*t);
}

double PrincipledBRDF::GTR2(double u, double a)
{
  double a2 = a*a;
  double t = 1.0 + (a2-1.0)*u*u;
  return a2 / (PI *t*t);
}

double PrincipledBRDF::smithG_GGX(double u, double alphaG)
{
    double a = alphaG*alphaG;
    double b = u*u;
    return 1.0/(u + std::sqrt(a + b - a*b));
}

double PrincipledBRDF::Schlick_fresnel(double u){
  double m = clamp(1.0 - u, 0.0,1.0);
  double m2 = m * m;
  return m2 * m2 * m;
}

Vect3 PrincipledBRDF::color()
{
    //Just return black
    return Vect3();
}

PrincipledBRDF& PrincipledBRDF::operator= (PrincipledBRDF const& d)
{
    if( this == &d)
        return (*this);

    BRDF::operator=(d);

    return (*this);
}
