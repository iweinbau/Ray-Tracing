#include <iostream>
#include <memory>
#include <fstream>
#include <math.h>
#include <algorithm>
#include <utility>
#include <functional>

#include "./Utils/Camera.hpp"
#include "./Utils/Vect3.hpp"
#include "./Utils/ray.hpp"
#include "Material/Material.hpp"
#include "./Objects/sphere.hpp"
#include "./Objects/Triangle.hpp"
#include "./Objects/Object.hpp"
#include "./Objects/Plane.hpp"
#include "./Material/Phong.hpp"
#include "./Material/Reflective.hpp"
#include "./Material/Mirror.hpp"
#include "./Light/Light.hpp"
#include "./Light/pointLight.hpp"
#include "tracer.hpp"
#include "./Utils/Hitinfo.hpp"


#include "./ThreadPool/ThreadPool.h"

void save_to_file(std::string filename, int width, int height, Vect3 const* pixels)
{
    // save frame buffer to file
    std::ofstream ofs;
    ofs.open(filename.append(".ppm"), std::ios::out | std::ios::binary);
    ofs << "P6\n" << width << " " << height << "\n255\n";
    for (int i = 0; i < height * width; ++i) {
        ofs << (unsigned char)(std::min(std::max(pixels[i].x_,0.0), 1.0)  * 255) <<
        (unsigned char)(std::min(std::max(pixels[i].y_, 0.0), 1.0) * 255) <<
        (unsigned char)(std::min(std::max(pixels[i].z_, 0.0), 1.0) * 255);
    }

    ofs.close();
}


void mul_render(int i, int j,int width, int height,Camera& camera,World& world,Vect3* pixels){
    tracer tr;
    int x, y;
    for (x = i; x < width; x++) {
        for (y = j; y < height; y++) {
            //construct a ray for through this pixel.
            Vect3 color;
            for(int n = 0; n < camera.num_samples;n++){
                Ray ray= camera.constructRay(x,y);
                color = color + tr.trace(ray,world, 2);
            }
            pixels[camera.height*x +y] = color/(double)(camera.num_samples);
        }
    }
}

int main() {
    std::cout << "Basic Ray tracing!\n";
    //construct a camera
	Vect3 lookfrom = Vect3(0, 0, 10);
	Vect3 lookat = Vect3(0, 0, 0);
	Camera camera(lookfrom, lookat, 90);

	//image setup
	const int size = camera.width * camera.height;
	Vect3* pixels = new Vect3[size];

    World builder;

    builder.buildWorld();


    ThreadPool th_pool(NUM_THREADS);
    th_pool.init();

    int chunck_width = camera.width/NUM_CHUNCKS;
    int chunck_height = camera.height/NUM_CHUNCKS;

    std::vector<std::future<void>> res;

    //create work for each chunk.
    for(int i=0;i<NUM_CHUNCKS;i++){
        for(int j=0;j<NUM_CHUNCKS;j++){
            res.push_back(th_pool.submit(mul_render,i*chunck_width,
                                    j*chunck_height,
                                    i*chunck_width+chunck_width,
                                    j*chunck_height+chunck_height,
                                    std::ref(camera),
                                    std::ref(builder),
                                    std::ref(pixels)));
        }
    }

    for (int t=0; t<res.size(); t++) {
        res[t].get();
    }

    th_pool.shutdown();

    save_to_file("out", camera.width, camera.height, pixels);
    return 0;
}
