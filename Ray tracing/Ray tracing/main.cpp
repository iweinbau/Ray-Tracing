#include <iostream>
#include <memory>
#include <fstream>
#include <math.h>
#include <algorithm>
#include <utility>

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

void save_to_file(char const* filename, int width, int height, Vect3 const* pixels)
{
    // save frame buffer to file
    std::ofstream ofs;
    ofs.open("./out.ppm", std::ios::out | std::ios::binary);
    ofs << "P6\n" << width << " " << height << "\n255\n";
    for (int i = 0; i < height * width; ++i) {
        ofs << (unsigned char)(std::min(std::max(pixels[i].x_,0.0), 1.0)  * 255) <<
        (unsigned char)(std::min(std::max(pixels[i].y_, 0.0), 1.0) * 255) <<
        (unsigned char)(std::min(std::max(pixels[i].z_, 0.0), 1.0) * 255);
    }
    
    ofs.close();
}

int main() {
    std::cout << "Basic Ray tracing!\n";
    tracer tr;

    //construct a camera
	Vect3 lookfrom = Vect3(0, 0, 10);
	Vect3 lookat = Vect3(0, 0, 0);
	Camera camera(lookfrom, lookat, 90);

	//image setup
	const int size = camera.width * camera.height;
	Vect3* pixels = new Vect3[size];
    
    World builder;
    
    builder.buildWorld();
    
	int x, y;
	int index = 0;
	for (x = 0; x < camera.height; x++) {
		for (y = 0; y < camera.width; y++) {
			//construct a ray for through this pixel.
            Vect3 color;
            for(int n = 0; n < camera.num_samples;n++){
                Ray ray= camera.constructRay(x,y);
                color = color + tr.trace(ray,builder, 2);
            }
            pixels[index++] = color/(double)(camera.num_samples);
		}
	}
    save_to_file("test.ppm", camera.width, camera.height, pixels);
    return 0;
}
