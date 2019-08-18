#include <iostream>
#include <memory>
#include <fstream>
#include <math.h>
#include <algorithm>
#include <utility>
#include <functional>

#include "./Utils/Constants.hpp"
#include "./Utils/Camera.hpp"
#include "./Utils/Vect3.hpp"
#include "./Utils/ray.hpp"
#include "./Utils/tracer.hpp"
#include "./Utils/GlobalTracer.hpp"


#include "./Utils/Hitinfo.hpp"
#include "./pngWriter/lodepng.h"

#include "./Builder/World.hpp"
#include "./Builder/StormTrooper.hpp"

#include "./Builder/TriangleWorld.hpp"


#include "./ThreadPool/ThreadPool.h"

double g = 1;

void save_to_file(std::string filename, int width, int height, Vect3 const* pixels)
{
  std::vector<unsigned char> image;
  image.resize(width * height * 4);
  for (unsigned i = 0; i < height * width; i++) {
      image[i * 4 +0] = pow(std::min(std::max(pixels[i].x_,0.0), 1.0),1.0/g)  * 255;
    image[i * 4 +1] = pow(std::min(std::max(pixels[i].y_,0.0), 1.0),1.0/g)  * 255;
    image[i * 4 +2] = pow(std::min(std::max(pixels[i].z_,0.0), 1.0),1.0/g)  * 255;
    image[i * 4 +3] = 255;
  }
  lodepng::encode(filename.append(".png"),image,width,height);
}


void mul_render(int x,int y,int width, int height,Camera* camera,World& world,Vect3* pixels,int width_offset=0, int height_offset=0){
    GlobalTracer tr;
    tracer t;
    //construct a ray for through this pixel.
    Vect3 color;
    for(int n = 0; n < NUM_SAMPLES;n++){
        Ray ray= camera->constructRay(x,y);
        color = color + tr.trace(ray,world,0);//+ t.trace(ray, world, 3);
    }
    pixels[width*(y-height_offset)+(x-width_offset)] = color/(double)(NUM_SAMPLES);
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
    if( argc != 7 && argc != 3){
        std::cout << "Check you used the right number of parameters:"<<std::endl;
        std::cout << "./raytracer NUM_THREADS OUT_FILE START_WIDTH END_WIDTH START_HEIGHT END_HEIGHT"<<std::endl;
        return -1;
    }
    //variables for timing.
    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();

    World builder;
    builder.buildWorld();

    //get num thread from command line argument.
    int NUM_THREADS = std::stoi(argv[1]);
    //get file name.
    std::string _outFile = argv[2];
    //thread setup.
    ThreadPool th_pool(NUM_THREADS);
    th_pool.init();

    int image_width = builder.camera->width;
    int image_height = builder.camera->height;
    int start_width = 0;
    int end_width = image_width;
    int start_height = 0;
    int end_height = image_height;

    if(argc == 7){
        //render only a part of the image.
        //define command line arugments.
        start_width = std::stoi(argv[3]);
        end_width = std::stoi(argv[4]);
        start_height = std::stoi(argv[5]);
        end_height = std::stoi(argv[6]);
        
        image_width=(end_width - start_width);
        image_height=(end_height - start_height);
    }
    
    std::vector<std::future<void>> res;

    //image setup
    const int size = image_width * image_height;
    Vect3* pixels = new Vect3[size];
    
    std::cout << "Basic Ray tracing!\n";
    std::cout << "Creating jobs..."<<std::endl;
    //create work for each chunk.
    //create work for each chunk.
    for(int x=start_width;x<end_width;x++){
        for(int y=start_height;y<end_height;y++){
            res.push_back(th_pool.submit(mul_render,x,y,
                                         image_width,
                                         image_height,
                                         builder.camera,
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
    std::cout << "Done!"<<std::endl;
    return 0;
}
