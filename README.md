<p align='center'>
<img src='https://raw.githubusercontent.com/iweinbau/Basic-Ray-Tracing/image/out.png' width=400/>
<img src='https://raw.githubusercontent.com/iweinbau/Basic-Ray-Tracing/image/glossy_render.png' width=400/>
<figcaption>Fig.1 - render scene, left perfect mirror reflections. Right glossy reflections.</figcaption>
</p>

# Basic ray-tracer in C++

The goal of this project is to get familiar with c++ and learn the basics of computer graphics.

## Current features 

 - Muliple plane and sphere objects
 - Multiple lights
 - Matte material, has only diffuse and ambient.
 - Phong material, has also specular using Bling-Phong.
 - Reflective material. Perfect mirror and glossy reflections.
 - Aliasing using random pixel sampling.

I'm still working and I'll add new features.

## Reflections
### Perfect reflections
First kind of reflection is the perfect mirror. Perfect reflected rays are cast recursively in the world. This calculate the incoming light. 

### Glossy reflections
Since most objects don't have a perfect reflective surface I've implemented glossy reflections (the reflection is blurred out) To achieve this effect multiple rays (samples) are cast randomly along the perfect reflective vector. We can controle the blur using a glossy factor. A larger factor means a more perfect reflected surface. More info on glossy reflectons in the sample chapter of [Ray tracer from the ground up](http://www.raytracegroundup.com/downloads/Chapter25.pdf)

Also see Fig 1 for a comparison.

## Aliasing

Removing the pixelated effect of sharp edges. For this I used per pixel sampling, cast multiple rays randomly spread in each pixel. This is gives us not the best result, because rays can group together, but it's easy to understand.

## Running the code
I provided a simple make file that compiles the code to an executable.

 1. Run `make` this creates a raytracer executable
 2. Then run `./raytracer` to run the program
 3. The output will be in an out.ppm file.

