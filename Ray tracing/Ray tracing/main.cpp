#include <iostream>
#include <memory>
#include <fstream>
#include <math.h>
#include <algorithm>
#include <utility>
#include <list>

#define PI 3.14159265


#include "vector3f.hpp"
#include "ray.hpp"
#include "./Objects/sphere.hpp"
#include "./Objects/Object.hpp"
#include "./Objects/Plane.hpp"
#include "./Material/Phong.hpp"
#include "./Material/Reflective.hpp"
#include "./Material/Mirror.hpp"
#include "./Light/Light.hpp"
#include "./Light/pointLight.hpp"
#include "tracer.hpp"
#include "./Material/Matte.hpp"
#include "Hitinfo.hpp"

//Class that stores information about the camara.
//In create camera rays from it pointing in the world based on the properties.
class Camera {
public:
    //resolution in pixels.
    static const int width = 800, height = 800;
    static const int num_samples = 5;
    Camera(Vect3 lookfrom, Vect3 lookat, double fovy):
    eye_(lookfrom),
    lookat_(lookat),
    fovy_(fovy),
    aspect_(double(width)/double(height)),
    direction_((lookat_ - lookfrom).normalize()),
    up_(Vect3(0,1,0)){ // fov is top to bottom in degrees
        
        //degree to radian convertion.
        double tetha = (fovy_ * PI) / 180;
        double view_width = tan(tetha / 2) * distance_;
        double view_height = view_width / aspect_;
        
        horizontal_ = view_width * 2;
        vertical_ = view_height * 2;
        

        Vect3 center = eye_ + ( direction_ * distance_);
        
        u = direction_.neg();
        n = (up_.cross(u)).normalize();
        v = u.cross(n);
        
        upper_corner_ = center + (n.neg() * view_width) + (v * view_height);
        
    }
    Ray constructRay(int i, int j) {
        std::random_device rd;  //Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
        std::uniform_real_distribution<> dis(0.0, 1.0);
        
        //From raytracing from the ground up.
        double x = dis(gen);
        double y = dis(gen);
        //calculate the ray.
        return Ray(eye_,(upper_corner_ + (n * (j+x) * (horizontal_/double(width))) + (v.neg() * (i+y) * (vertical_/double(height)))) - eye_);
    }
private:
    const double distance_ = 1;
    //the position of the camera;
    Vect3 eye_;
    Vect3 up_;
    Vect3 lookat_;
    Vect3 direction_;
    double fovy_;
    double aspect_;
    Vect3 upper_corner_;
    //the horizontal vector/of the image view.
    double horizontal_;
    //the vertical vector of the image view.
    double vertical_;
    
    //unit vectors of the camera axis.
    Vect3 u, v, n;
};

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

	//World setup
	//PointLight light(Vect3(1, 1,1), Vect3(5,5, -5),500);
    Light light2(Vect3(0.8, 0.8,0.8), Vect3(-5,0, 5),1);

    Reflective phong(
                Lambertian(0.25,Vect3(0.3,0.3,0.3)),
                Lambertian(0.6,Vect3(0.4,0.4,0.4)),
                Specular(0.2,5,Vect3(0.6,0.6,0.6)),
                Glossy(0.9,50,Vect3(1,1,1)));

	Sphere sphere(Vect3(3, 0, 0), 3, &phong);
    
    Phong phong2(
                Lambertian(1,Vect3(0.0,0.3,0)),
                Lambertian(0.6,Vect3(0,1,0)),
                Specular(0.2,5,Vect3(1,1,1)));

    //
    Sphere sphere2(Vect3(-3, -2, -5), 2, &phong2);
    
    Phong phong3(
                 Lambertian(0.25,Vect3(0.3,0,0)),
                 Lambertian(0.6,Vect3(0.8,0,0)),
                 Specular(0.2,5,Vect3(1,1,1)));
    
    //
    Sphere sphere3(Vect3(5, 5, -10), 3,&phong3);
    
    Phong planem(
                     Lambertian(0.25,Vect3(0.8,0.8,0.8)),
                     Lambertian(0.6,Vect3(0.8,0.8,0.8)),
                     Specular(0.2,5,Vect3(1,1,1)));
    Phong planeb(
                 Lambertian(0.25,Vect3(0.8,0.8,0.8)),
                 Lambertian(0.6,Vect3(0.8,0.8,0.8)),
                 Specular(0.2,1,Vect3(1,1,1)));
    
    Phong planel(
                 Lambertian(0.25,Vect3(0.8,0,0)),
                 Lambertian(0.6,Vect3(0.8,0,0)),
                 Specular(0.2,5,Vect3(1,1,1)));
    Phong planer(
                 Lambertian(0.25,Vect3(0,0.8,0)),
                 Lambertian(0.5,Vect3(0,0.8,0)),
                 Specular(0.2,5,Vect3(1,1,1)));
    
    Plane planeback(Vect3(0, 0, -20), Vect3(0,0,1),&planem);
    Plane planeleft(Vect3(-20, 0, 0), Vect3(1,0,0),&planel);
    Plane planeright(Vect3(20, 0, 0), Vect3(-1,0,0),&planer);
    Plane planebottom(Vect3(0, -10, 0), Vect3(0,1,0),&planem);
    Plane planetop(Vect3(0, 20, 0), Vect3(0,-1,0),&planem);




    
	//create objects.
    std::vector<Object*> objects;
    objects.push_back(&sphere3);
	objects.push_back(&sphere2);
    objects.push_back(&sphere);
    objects.push_back(&planeback);
    objects.push_back(&planeleft);
    objects.push_back(&planeright);
    objects.push_back(&planebottom);
    objects.push_back(&planetop);
    

	//create lights.
    std::vector<Light*> lights;
	//lights.push_back(&light);
    lights.push_back(&light2);

	int x, y;
	int index = 0;
	for (x = 0; x < camera.height; x++) {
		for (y = 0; y < camera.width; y++) {
			//construct a ray for through this pixel.
            Vect3 color;
            for(int n = 0; n < camera.num_samples;n++){
                Ray ray = camera.constructRay(x,y);
                color = color + tr.trace(ray,objects, lights, 2);
            }
            pixels[index++] = color/(double)(camera.num_samples);
		}
	}
    save_to_file("test.ppm", camera.width, camera.height, pixels);
    return 0;
}
