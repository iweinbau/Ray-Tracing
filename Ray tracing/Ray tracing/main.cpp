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

#include "./Builder/World.hpp"
#include "./Builder/TriangleWorld.hpp"


#include "./ThreadPool/ThreadPool.h"

void save_to_file(std::string filename, int width, int height, Vect3 const* pixels)
{
    // save frame buffer to file
    std::ofstream ofs;
    ofs.open(filename.append(".ppm"), std::ios::out | std::ios::binary);
    ofs << "P6\n" << width << " " << height << "\n255\n";
    for (int i = 0; i < height * width; i++) {
        ofs << (unsigned char)(std::min(std::max(pixels[i].x_,0.0), 1.0)  * 255) <<
        (unsigned char)(std::min(std::max(pixels[i].y_, 0.0), 1.0) * 255) <<
        (unsigned char)(std::min(std::max(pixels[i].z_, 0.0), 1.0) * 255);
    }

    ofs.close();
}


void mul_render(int start_width, int start_height,
                int end_width, int end_height,int width, int height,
                Camera& camera,World& world,Vect3* pixels,
                int width_offset=0, int height_offset=0){
    tracer tr;
    int x, y;
    for (y = start_height; y < end_height; y++) {
        for (x = start_width; x < end_width; x++) {
            //construct a ray for through this pixel.
            Vect3 color;
            for(int n = 0; n < camera.num_samples;n++){
                Ray ray= camera.constructRay(y,x);
                color = color + tr.trace(ray,world, 2);
            }
            pixels[width*(y-height_offset) +(x-width_offset)] = color/(double)(camera.num_samples);
        }
    }
}

int main(int argc, char* argv[]) {
  if( argc <= 1){
    std::cout << "Give first arugment NUM_THREADS" << std::endl;
    return -1;
  }

    if( argc <= 2){
        std::cout << "Give second argument output file" << std::endl;
        return -1;
    }
  //variables for timing.
  auto start = std::chrono::high_resolution_clock::now();;
  auto end = std::chrono::high_resolution_clock::now();

    //construct a camera
	Vect3 lookfrom = Vect3(0, 0, 10);
	Vect3 lookat = Vect3(0, 0, 0);
	Camera camera(lookfrom, lookat, 90);

  World builder;
  builder.buildWorld();

  //get num thread from command line argument.
  int NUM_THREADS = std::stoi(argv[1]);
    //get file name.
    std::string _outFile = argv[2];
  //thread setup.
  ThreadPool th_pool(NUM_THREADS);
  th_pool.init();

  std::cout << "Basic Ray tracing!\n";
  // render hole image.
  if( argc == 3 ){
    int image_width = camera.width;
    int image_height = camera.height;
    //image setup
    const int size = image_width * image_height;
    Vect3* pixels = new Vect3[size];

    int chunck_width = image_width/NUM_CHUNCKS;
    int chunck_height = image_height/NUM_CHUNCKS;

    std::vector<std::future<void>> res;

    std::cout << "Creating jobs..."<<std::endl;
    //create work for each chunk.
    for(int i=0;i<NUM_CHUNCKS;i++){
        for(int j=0;j<NUM_CHUNCKS;j++){
            res.push_back(th_pool.submit(mul_render,i*chunck_width,
                                    j*chunck_height,
                                    i*chunck_width+chunck_width,
                                    j*chunck_height+chunck_height,
                                    image_width,
                                    image_height,
                                    std::ref(camera),
                                    std::ref(builder),
                                    std::ref(pixels),0,0));
        }
    }
    std::cout << "Jobs created"<<std::endl;
    std::cout << "Rendering..."<<std::endl;

    start = std::chrono::high_resolution_clock::now();
    for (int t=0; t<res.size(); t++) {
        res[t].get();
    }
    end = std::chrono::high_resolution_clock::now();

    std::cout << "Finished render in: " << std::chrono::duration<double>(end-start).count()<<std::endl;

    std::cout << "Closing threads..."<<std::endl;
    th_pool.shutdown();
    std::cout << "Writing to image..."<<std::endl;
    save_to_file(_outFile, image_width, image_height, pixels);
  }else{
    //render only a part of the image.
    //define command line arugments.
    int start_width = std::stoi(argv[3]);
    int end_width = std::stoi(argv[4]);
    int start_height = std::stoi(argv[5]);
    int end_height = std::stoi(argv[6]);     

    int image_width=(end_width - start_width);
    int image_height=(end_height - start_height);

    int chunck_width = image_width/NUM_CHUNCKS;
    int chunck_height = image_height/NUM_CHUNCKS;

    std::vector<std::future<void>> res;

    //image setup
    const int size = image_width * image_height;
    Vect3* pixels = new Vect3[size];

    std::cout << "Creating jobs..."<<std::endl;
    //create work for each chunk.
    for(int i=0;i<NUM_CHUNCKS;i++){
        for(int j=0;j<NUM_CHUNCKS;j++){
            res.push_back(th_pool.submit(mul_render,i*chunck_width + start_width,
                                    j*chunck_height + start_height,
                                    i*chunck_width+chunck_width + start_width,
                                    j*chunck_height+chunck_height + start_height,
                                    image_width,
                                    image_height,
                                    std::ref(camera),
                                    std::ref(builder),
                                    std::ref(pixels),start_width,start_height));
        }
    }
    std::cout << "Jobs created"<<std::endl;
    std::cout << "Rendering..."<<std::endl;
    start = std::chrono::high_resolution_clock::now();
    for (int t=0; t<res.size(); t++) {
        res[t].get();
    }
    end = std::chrono::high_resolution_clock::now();

    std::cout << "Finished render in: " << std::chrono::duration<double>(end-start).count()<<std::endl;

    std::cout << "Closing threads..."<<std::endl;
    th_pool.shutdown();
    std::cout << "Writing to image..."<<std::endl;
    save_to_file(_outFile, image_width, image_height, pixels);
  }
  std::cout << "Done!"<<std::endl;
  return 0;
}
