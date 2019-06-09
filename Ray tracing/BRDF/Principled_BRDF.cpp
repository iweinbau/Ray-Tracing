#include "../Utils/Constants.hpp"
#include "Principled_BRDF.hpp"
#include "../Material/Disney.hpp"
#include <random>
#include "math.h"

#include "../Utils/Math.hpp"

PrincipledBRDF::PrincipledBRDF():BRDF()
{}

PrincipledBRDF::~PrincipledBRDF()
{}

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

Vect3 PrincipledBRDF::sample(Disney* mat,Hitinfo const& hitinfo, Vect3 const& wo)
{
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(0.0, 1.0);
    
    double ratiodiffuse = (1 - mat->metallic)/2;
    double p = dis(gen);
    
    Vect3 w = hitinfo.normal;
    Vect3 v = Vect3(0.0034, 1, 0.0071).cross(w);
    v = v.normalize();
    Vect3 u = v.cross(w);
    
    //From raytracing from the ground up.
    double x = dis(gen);
    double y = dis(gen);
    
    Vect3 wi;
    
    if( p < ratiodiffuse){
        //sample diffuse lobe
        double cos_phi = cos(2.0 * PI * x);
        double sin_phi = sin(2.0 * PI * x);
        double cos_theta = pow((1.0 - y), 1.0 / (1.0+1.0));
        double sin_theta = sqrt (1.0 - cos_theta * cos_theta);
        
        double pu = sin_theta * cos_phi;
        double pv = sin_theta * sin_phi;
        double pw = cos_theta;
        
        wi = u * pu + v * pv + w * pw;
        wi = wi.normalize();
    }else{
        //sample specular lobe.
        float a = std::max(0.001, mat->roughness);
        
        float phi = x * 2.0 * PI;
        
        float cosTheta = sqrt((1.0 - y) / (1.0 + (a*a-1.0) *y));
        float sinTheta = sqrt(1.0 - (cosTheta * cosTheta));
        float sinPhi = sinf(phi);
        float cosPhi = cosf(phi);
        
        Vect3 half = Vect3(sinTheta*cosPhi, sinTheta*sinPhi, cosTheta);
        half = u * half.x_ + v * half.y_ + w * half.z_;
        half = half.normalize();
        
        wi = half* 2.0* wo.dot(half) - wo; //reflection vector
        wi = wi.normalize();
    }
    
    return wi;
}


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
    float Cdlum = 0.3*Cdlin.x_ + 0.6*Cdlin.y_ + 0.1*Cdlin.z_; // luminance approx.
    
    Vect3 Ctint = Cdlum > 0.0 ? Cdlin / Cdlum : Vect3(1.0); // normalize lum. to isolate hue+sat
    Vect3 Cspec0 = lerp(mat->specular*0.08*lerp(Vect3(1.0), Ctint, mat->specularTint), Cdlin, mat->metallic);
    Vect3 Csheen = lerp(Vect3(1.0), Ctint, mat->sheenTint);
    
    
    double Fd90 = 0.5 + 2*ndoth * ndoth * mat->roughness;
    double Fi = fresnel(ndotwi);
    double Fo = fresnel(ndotwo);
    
    double Fd = (1 + (Fd90-1)*Fi)*(1 + (Fd90-1)*Fo);
    
    double Fss90 = widoth*widoth*mat->roughness;
    double Fss = lerp(Fi,1.0,Fss90) * lerp(Fo,1.0,Fss90);
    double ss = 1.25 * (Fss * (1.0 / (ndotwi + ndotwo) - 0.5) + 0.5);
    
    float a = std::max(0.001, mat->roughness);
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
