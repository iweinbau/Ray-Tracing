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
class Light {
public:
    Light(Vect3 diffuse, Vect3 specular, Vect3 position):
    diffuse_(diffuse),
    specular_(specular),
    position_(position)
    {}
    Vect3 getPosition() {
        return position_;
    }
    Vect3 getDiffuse() {
        return diffuse_;
    }
    Vect3 getSpecular() {
        return specular_;
    }
private:
    Vect3 specular_;
    Vect3 diffuse_;
    Vect3 position_;
    
};
void save_to_file(char *filename, int width, int height, Vect3 *pixels)
{
    // save frame buffer to file
    std::ofstream ofs;
    ofs.open("./out.ppm", std::ios::out | std::ios::binary);
    ofs << "P6\n" << width << " " << height << "\n255\n";
    for (int i = 0; i < height * width; ++i) {
        ofs << (unsigned char)(min(std::max(pixels[i].x_,0.0), 1.0)  * 255) <<
        (unsigned char)(min(max(pixels[i].y_, 0.0), 1.0) * 255) <<
        (unsigned char)(min(max(pixels[i].z_, 0.0), 1.0) * 255);
    }
    
    ofs.close();
}


Vect3 shade(Ray ray, list<Sphere> objects, Light l, int depth) {
	Vect3 color = Vect3(); //set initial color to background.
    
    
	double tmin = INFINITY;
    double t;
    Sphere closest;
    Vect3 intersection;
    Vect3 tmp;
    
    bool hit = false;
    for(Sphere obj : objects){
        if (obj.hit(ray, tmp, t)) {
            if (t < tmin) {
                //we found a closer object.
                intersection = tmp;
                closest = obj;
                tmin = t;
                hit = true;
            }
        }
    }
    
	if (hit) {
        
        Vect3 surfaceNormal = closest.getNormalAtPoint(intersection);
        Vect3 lightDir = (l.getPosition() - intersection).normalize();

        //********** AMBIENT COLOR ********** \\
		//set color to ambient light.
		color = closest.material_.ambientColor;
        
        //********* CAST SHADOW RAY ********** \\
        //cast shadow ray to check if the object is in shadow.
        Ray shadowray(intersection + surfaceNormal * 0.0001,lightDir);
        
        hit = false;
        double maxt = (l.getPosition() - intersection).length();
        for(Sphere obj : objects){
            if (obj.hit(shadowray, intersection, t)) {
                if(t < maxt){
                    hit = true;
                    break;
                }
            }
        }
        // if we hit again this object is in shadow no need to caluculate specular and diffuse.
        //********** SPECULAR and DIFFUSE factor for each light ********** \\
        //calculate the diffuse and specular color
        if(!hit){
            Vect3 tmp = Vect3();
                Vect3 viewDir = (ray.origin_ - intersection).normalize();
                //DIFFUSE COLOR
                double intensity = max((double)0, lightDir.dot(surfaceNormal));
                Vect3 diffuse= closest.material_.diffuseColor * intensity * l.getDiffuse();
            
                //SPECULAE COLOR;
                Vect3 H = (lightDir + viewDir).normalize();
                // Intensity of specular light
                double NdotH = surfaceNormal.dot(H);
                intensity = pow(NdotH,closest.material_.shininess);
                Vect3 specular = closest.material_.specularColor * l.getSpecular() * intensity;
            
                //TOTAL COLOR:
                //USING BLING-PHONG
                color = color + diffuse + specular;
        }
        //Calculate reflective color by calling shader recursively
        //if depth is less or equal to 0 stop tracing reflection.
        if (closest.material_.reflection && depth >= 0) {
            Vect3 reflection = (ray.direction_ - surfaceNormal * 2 * surfaceNormal.dot(ray.direction_)).normalize();
            Ray reflectionRay = Ray(intersection + reflection * 0.0001, reflection);
            //add the reflection ray to the current color.
            color = color + shade(reflectionRay, objects, l, depth - 1) * closest.material_.reflection;
        }
    }
    return color;
}

int main() {
	cout << "Basic Ray tracing!\n";

	//construct a camera 
	Vect3 lookfrom = Vect3(0, 0, 10);
	Vect3 lookat = Vect3(0, 0, 0);
	Camera camera(lookfrom, lookat, 45);

	//image setup
	const int size = camera.width * camera.height;
	Vect3* pixels = new Vect3[size];

	//World setup
	Light light = Light(Vect3(1, 1,1),Vect3(1,1,1) , Vect3(0,0, 5));

    // Red sphere
	Sphere sphere(Vect3(-2, 3, -4), 2, material(Vect3(0.3,0,0),Vect3(1, 0, 0),Vect3(1,1,1),50,2));
    //
    Sphere sphere2(Vect3(0, -2, -5), 2, material(Vect3(0,0.3,0),Vect3(0, 1, 0),Vect3(1,1,1),30,2));
    
    //
    Sphere sphere3(Vect3(2, -2, -30), 10, material(Vect3(0.3,0.3,0.3),Vect3(0.5, 0.5, 0.5),Vect3(1,1,1),30,2));
    
	//create objects.
	list<Sphere> objects;
	objects.push_back(sphere2);
    objects.push_back(sphere3);
    objects.push_back(sphere);
    //objects.push_back(&sphere3);


	//create lights.
	list<Light> lights;
	lights.push_back(light);


	int x, y;
	int index = 0;
	for (x = 0; x < camera.height; x++) {
		for (y = 0; y < camera.width; y++) {
			//construct a ray for through this pixel.
			Ray ray = camera.constructRay(x,y);
			pixels[index++] = shade(ray,objects, light, 2);
		}
	}
    save_to_file("test.bmp", camera.width, camera.height, pixels);
    return 0;
}
