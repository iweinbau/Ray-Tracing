#include "../Utils/Constants.hpp"
#include "Principled_BRDF.hpp"
#include "../Material/Disney.hpp"
#include "BRDF.hpp"
#include <random>
#include "math.h"

#include "../Utils/Math.hpp"

PrincipledBRDF::PrincipledBRDF():BRDF()
{}

PrincipledBRDF::~PrincipledBRDF()
{}

PrincipledBRDF* PrincipledBRDF::clone() {
    return new PrincipledBRDF(*this);
}

//http://simon-kallweit.me/rendercompo2015/report/
double PrincipledBRDF::pdf(Disney* mat,Hitinfo const& hitinfo, Vect3 const& wi, Vect3 const& wo){
    Vect3 n = hitinfo.normal;
    
    float specularAlpha = std::max(0.001, mat->roughness);
    float clearcoatAlpha = lerp(mat->clearcoatGloss,0.1, 0.001);
    
    float diffuseRatio = 0.5 * (1.0 - mat->metallic);
    float specularRatio = 1.0 - diffuseRatio;
    
    Vect3 half = (wi+wo).normalize();
    
    float cosTheta = abs(half.dot(n));
    float pdfGTR2 = GTR2(cosTheta, specularAlpha) * cosTheta;
    float pdfGTR1 = GTR1(cosTheta, clearcoatAlpha) * cosTheta;
    
    // calculate diffuse and specular pdfs and mix ratio
    float ratio = 1.0 / (1.0 + mat->clearcoat);
    float pdfSpec = lerp(ratio,pdfGTR1, pdfGTR2) / (4.0 * abs(wi.dot(half)));
    float pdfDiff = abs(wi.dot(n))* (1.0 / PI);
    
    // weight pdfs according to ratios
    return diffuseRatio * pdfDiff + specularRatio * pdfSpec;
}

Vect3 PrincipledBRDF::sample_f(Disney* mat,Hitinfo const& hitinfo, Vect3 const& wo)
{
    
    double ratiodiffuse = (1 - mat->metallic)/2;
    double p = sampler.sample();
    
    Vect3 w = hitinfo.normal;
    Vect3 v = Vect3(0.0034, 1, 0.0071).cross(w);
    v = v.normalize();
    Vect3 u = v.cross(w);
    
    Vect3 wi;
    
    if( p < ratiodiffuse){
        //sample diffuse lobe
        
        Point3 p = sampler.sampleOnHemisphere();
        
        wi = u * p.x_ + v * p.y_ + w * p.z_;
        wi = wi.normalize();
    }else{
        //sample specular lobe.
        double a = std::max(0.001, mat->roughness);
        double x = sampler.sample();
        double y = sampler.sample();
        
        double phi = x * 2.0 * PI;
        
        double cosTheta = sqrt((1.0 - y) / (1.0 + (a*a-1.0) *y));
        double sinTheta = sqrt(1.0 - (cosTheta * cosTheta));
        double sinPhi = sinf(phi);
        double cosPhi = cosf(phi);
        
        Vect3 half = Vect3(sinTheta*cosPhi, sinTheta*sinPhi, cosTheta);
        half = u * half.x_ + v * half.y_ + w * half.z_;
        half = half.normalize();
        
        wi = half* 2.0* wo.dot(half) - wo; //reflection vector
        wi = wi.normalize();
        
    }
    
    return wi;
}

//From https://github.com/wdas/brdf/blob/master/src/brdfs/disney.brdf.
//TODO add anisotropic values.
Vect3 PrincipledBRDF::eval(Disney* mat,Hitinfo const& hitinfo,Vect3 const& wi,Vect3 const& wo){
    // halfway vector;
    Vect3 wh = (wi + wo).normalize();
    
    double ndoth = hitinfo.normal.dot(wh);
    double ndotwi = hitinfo.normal.dot(wi);
    double ndotwo = hitinfo.normal.dot(wo);
    double widoth = wi.dot(wh);
    
    if(ndotwi <=0 || ndotwo <= 0)
        return Vect3();
    
    Vect3 Cdlin = mat->baseColor;
    double Cdlum = 0.3*Cdlin.x_ + 0.6*Cdlin.y_ + 0.1*Cdlin.z_; // luminance approx.
    
    Vect3 Ctint = Cdlum > 0.0 ? Cdlin / Cdlum : Vect3(1.0); // normalize lum. to isolate hue+sat
    Vect3 Cspec0 = lerp(mat->metallic,mat->specular*0.08*lerp(mat->specularTint,Vect3(1.0), Ctint), Cdlin);
    Vect3 Csheen = lerp(mat->sheenTint,Vect3(1.0), Ctint);
    
    
    //DIFUSE
    double Fd90 = 0.5 + 2*ndoth * ndoth * mat->roughness;
    double Fi = fresnel(ndotwi);
    double Fo = fresnel(ndotwo);
    
    double Fd = (1 + (Fd90-1)*Fi)*(1 + (Fd90-1)*Fo);
    
    double Fss90 = widoth*widoth*mat->roughness;
    double Fss = lerp(Fi,1.0,Fss90) * lerp(Fo,1.0,Fss90);
    double ss = 1.25 * (Fss * (1.0 / (ndotwi + ndotwo) - 0.5) + 0.5);
    
    double a = std::max(0.001, mat->roughness);
    //specular D
    double Ds = GTR2(ndoth, a);
    //clearcoat D
    double Dc = GTR1(ndoth,lerp(mat->clearcoatGloss,0.1,0.001));
    
    //specular G
    double roughg = std::sqrt(mat->roughness*0.5 + 0.5);
    double Gs = GGX(ndotwo, roughg) * GGX(ndotwi,roughg);
    //clearcoat G
    double Gc = GGX(ndotwo, 0.25) * GGX(ndotwi, 0.25);
    
    //specular F
    double Fh = fresnel(widoth);
    // F = F0 + (1-F0)Fh -> F0 = lepr(Fh,
    Vect3 Fs = lerp(Fh,Cspec0,Vect3(1));
    //clearcoat F
    double Fc = lerp(Fh,0.04, 1.0);
    
    // sheen
    Vect3 Fsheen = Fh * mat->sheen * Csheen;
    
    return ((1/PI) * lerp(mat->subsurface, Fd, ss)*Cdlin + Fsheen)*(1.0 - mat->metallic)+ Gs*Fs*Ds + 0.25*mat->clearcoat*Gc*Fc*Dc;
}
