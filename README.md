
<p align='center'>
<img src='https://raw.githubusercontent.com/iweinbau/Ray-Tracing/image/out_global_500.strormtrooper.png' width=800/>
<figcaption>Rendered Stoormtrooper (800x800 using 1000 samples per pixel), credits to <a href='https://www.blendswap.com/blends/view/76637'>Scottgram</a> providing this scene. This was rendered using indirect lighting and using the <a href='https://disney-animation.s3.amazonaws.com/library/s2012_pbs_disney_brdf_notes_v2.pdf'>Disney principled BRDF</a>
</figcaption>
</p>

# Ray-tracer in C++

The goal of this project is to get familiar with c++ and learn the basics of computer graphics. View design on [google drive](https://drive.google.com/open?id=1AycpsDItILuk4ehFi2Kk7ZPwQ3XedO23)

## Current features 

 - Multiple plane and sphere objects
 - Multiple lights
 - Matte material, has only diffuse and ambient.
 - Phong material, has also specular using Bling-Phong.
 - Reflective material. Perfect mirror and glossy reflections.
 - Aliasing using random pixel sampling.
 - Ambient occlusion
 - Area Lights/Soft shadows.
 - Global illumination.

## Reflections
### Perfect reflections
First kind of reflection is the perfect mirror. Perfect reflected rays are cast recursively in the world. This calculates the incoming light. 

### Glossy reflections
Since most objects don't have a perfect reflective surface I've implemented glossy reflections (the reflection is blurred out). To achieve this effect multiple rays (samples) are cast randomly along the perfect reflective vector. We can control the blur using a glossy factor. A larger factor means a more perfect reflected surface. More info on glossy reflections can be found in the sample chapter of [Ray tracer from the ground up](http://www.raytracegroundup.com/downloads/Chapter25.pdf)

## Ambient occlusion
Ambient occusion let us variate the ambient color an object receives by checking how much of the hemishere above a hit point is blocked. Each scene has an ambient light class that samples random directions on the hemisphere and checks if this direction is blocked.

<p align='center'>
<img src='https://raw.githubusercontent.com/iweinbau/Ray-Tracing/image/ambient_occ_factor_0.png' width=400/>
<img src='https://raw.githubusercontent.com/iweinbau/Ray-Tracing/image/ambient_occ_factor_05.png' width=400/>
<figcaption>Fig.2 - render scene, left ambient occlusion with factor 0, Right left ambient occlusion with factor 0.5 (800x800-10 samples per pixel).</figcaption>
</p>

## Aliasing

Removing the pixelated effect of sharp edges. For this I used per pixel sampling, cast multiple rays randomly spread in each pixel. This doesn't give us the best result, because rays can group together, but it's easy to understand.

## Transforming

There is support for transforming objects using a transformation matrix. This is used in combination with instancing (resusing objects with diffrent transfomations), This limit memory usage.

## BRDF

THis project contains several BRDFs which are used in the material class.

 - Lambertian BRDF
 - Specular BRDF:  Used for specular reflections
 - Glossy BRDF: Used for glossy reflections.
 - Disney BRDF: Implemented the [Disney BRDF](https://disney-animation.s3.amazonaws.com/library/s2012_pbs_disney_brdf_notes_v2.pdf) 

Each of this has 3 main functions. 
 1. `sample_f` which samples a reflected light vector in the corresponding lobe.
 2. `pdf` This returns the probability density function of the samples. Used for Monte Carlo estimator.
 3. `eval` This evalutate the BRDF.

## Material

**Matte**
This material has no specular highlights and has the following parameters

 - **cd** diffuse color
 - **kd** diffuse factor

for direct illumination it has also ambient parameters

 - **ca** ambient color
 - **ka** ambient factor

**Phong**
Has the same values as matte but it has an extra specular component.

 - **ks** specular intensity
 - **cs** specular color
 - **e** specular exponent, the higher values the sharper the specular reflection.

**Mirror**
Perfect mirror reflections. It has the same parameters as Phong but with extra specular reflection component.

 - **ks** reflection intensity
 - **cs** reflection color

**Glossy**
Glossy reflections. It has the same parameters as Phong but with extra glossy reflection component.

 - **ks** reflection intensity
 - **cs** reflection color
 - **e** specular exponent, the higher values the sharper the reflection.

**Disney**
This material is an implementation of the Disney BRDF
 - **baseColor**
 - **metallic**
 - **subsrface**
 - **specular**
 - **roughness**
 - **specularTint**
 - **sheen**
 - **sheenTint**
 - **clearcoat**
 - **clearcoatGloss**

For more information I refer to the [Disney BRDF paper](https://disney-animation.s3.amazonaws.com/library/s2012_pbs_disney_brdf_notes_v2.pdf).

## Running the code
I provided a simple make file that compiles the code to an executable.

 1. Run `make` this creates a raytracer executable
 
 ### Command line options
 There are 2 ways of rendering an immage. The first way is render the complete image. Then use `./raytracer OUT_FILE_NAME NUM_THREADS` where NUM_THREADS is replaces with the number of threads and  OUT_FILE_NAME the output file without exention. An other way is rendering a part of the image. Then you can specify the start pixel and end pixel as follows: `./raytracer NUM_THREADS OUT_FILE_NAME start_width end_width start_height end_height`.
 
The output will be the OUT_FILE_NAME.png

