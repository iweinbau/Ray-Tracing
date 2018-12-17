#include <iostream>
#include <memory>
#include <fstream>
#include <math.h>
#include <algorithm>
#include <utility>
#include <list>

#include "vector3f.hpp"
#include "ray.hpp"
#include "material.hpp"
#include "sphere.hpp"
#include "Phong.hpp"
#include "Reflective.hpp"
#include "Light.hpp"
#include "tracer.hpp"
#include "Hitinfo.hpp"

#define PI 3.14159265

//Class that stores information about the camara.
//In create camera rays from it pointing in the world based on the properties.
class Camera {
public:
    //resolution in pixels.
    const int width = 600, height = 600;
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
        //calculate the ray.
        return Ray(eye_,(upper_corner_ + n * j * (horizontal_/double(width)) + v.neg() * i * (vertical_/double(height))) - eye_);
    }
private:
    double distance_ = 1;
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

void save_to_file(char *filename, int width, int height, Vect3 *pixels)
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
	Camera camera(lookfrom, lookat, 45);

	//image setup
	const int size = camera.width * camera.height;
	Vect3* pixels = new Vect3[size];

	//World setup
	Light light = Light(Vect3(0.5, 0.5,0.5),Vect3(0.5,0.5,0.5) , Vect3(10,0, 5));
    Light light2 = Light(Vect3(1, 1,1),Vect3(1,1,1) , Vect3(-5,0, 5));

    Reflective phong(
                Lambertian(1,Vect3(0.3,0,0)),
                Lambertian(1,Vect3(1.0,0,0)),
                Specular(30,Vect3(1,1,1)),3);
    phong.tr = tr;

    // Red sphere
	Sphere sphere(Vect3(-2, 2, -4), 2, &phong);
    
    Phong phong2(
                Lambertian(1,Vect3(0.0,0.3,0)),
                Lambertian(1,Vect3(0,1,0)),
                Specular(30,Vect3(1,1,1)));

    //
    Sphere sphere2(Vect3(0, -2, -5), 2, &phong2);
    
    Phong phong3(
                 Lambertian(1,Vect3(0.3,0.3,0.3)),
                 Lambertian(1,Vect3(0.8,0.8,0.8)),
                 Specular(30,Vect3(1,1,1)));
    
    //
    Sphere sphere3(Vect3(5, 5, -30), 10,&phong3);
    
	//create objects.
    std::list<Sphere> objects;
	objects.push_back(sphere2);
    objects.push_back(sphere3);
    objects.push_back(sphere);

	//create lights.
    std::list<Light> lights;
	lights.push_back(light);
    lights.push_back(light2);

	int x, y;
	int index = 0;
	for (x = 0; x < camera.height; x++) {
		for (y = 0; y < camera.width; y++) {
			//construct a ray for through this pixel.
			Ray ray = camera.constructRay(x,y);
            pixels[index++] = tr.trace(ray,objects, lights, 2);
		}
	}
    save_to_file("test.bmp", camera.width, camera.height, pixels);
    return 0;
}
