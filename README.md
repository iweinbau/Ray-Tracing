<p align='center'>
<img src='https://raw.githubusercontent.com/iweinbau/Basic-Ray-Tracing/image/out.png' width=400/>
<img src='https://raw.githubusercontent.com/iweinbau/Basic-Ray-Tracing/image/glossy_render.png' width=400/>
<figcaption>Fig.1 - render scene, left perfect mirror reflections. Right glossy reflections.</figcaption>
</p>

# Basic ray-tracer in C++

The goal of this project is to get familiar with c++ and learn the basics of computer graphics.

## Current features 

 - Multiple plane and sphere objects
 - Multiple lights
 - Matte material, has only diffuse and ambient.
 - Phong material, has also specular using Bling-Phong.
 - Reflective material. Perfect mirror and glossy reflections.
 - Aliasing using random pixel sampling.
 - Ambient occlusion
 - Area Lights/Soft shadows.

I'm still working and I'll add new features.

## Reflections
### Perfect reflections
First kind of reflection is the perfect mirror. Perfect reflected rays are cast recursively in the world. This calculates the incoming light. 

### Glossy reflections
Since most objects don't have a perfect reflective surface I've implemented glossy reflections (the reflection is blurred out). To achieve this effect multiple rays (samples) are cast randomly along the perfect reflective vector. We can control the blur using a glossy factor. A larger factor means a more perfect reflected surface. More info on glossy reflections can be found in the sample chapter of [Ray tracer from the ground up](http://www.raytracegroundup.com/downloads/Chapter25.pdf)

Also see Fig 1 for a comparison.

## Ambient occlusion
Ambient occusion let us variate the ambient color an object receives by checking how much of the hemishere above a hit point is blocked. Each scene has an ambient light class that samples random directions on the hemisphere and checks if this direction is blocked.

<p align='center'>
<img src='https://raw.githubusercontent.com/iweinbau/Basic-Ray-Tracing/image/ambient_occ_factor_0.png' width=400/>
<img src='https://raw.githubusercontent.com/iweinbau/Basic-Ray-Tracing/image/ambient_occ_factor_05.png' width=400/>
<figcaption>Fig.2 - render scene, left ambient occlusion with factor 0, Right left ambient occlusion with factor 0.5.</figcaption>
</p>

## Aliasing

Removing the pixelated effect of sharp edges. For this I used per pixel sampling, cast multiple rays randomly spread in each pixel. This doesn't give us the best result, because rays can group together, but it's easy to understand.

## Transforming

There is support for transforming objects using a transformation matrix. This is used in combination with instancing (resusing objects with diffrent transfomations), This limit memory usage.

## Running the code
I provided a simple make file that compiles the code to an executable.

 1. Run `make` this creates a raytracer executable
 
 ### Command line options
 There are 2 ways of rendering an immage. The first way is render the complete image. Then use `./raytracer OUT_FILE_NAME NUM_THREADS` where NUM_THREADS is replaces with the number of threads and  OUT_FILE_NAME the output file without exention. An other way is rendering a part of the image. Then you can specify the start pixel and end pixel as follows: `./raytracer NUM_THREADS OUT_FILE_NAME start_width end_width start_height end_height`.
 
The output will be the OUT_FILE_NAME.ppm

