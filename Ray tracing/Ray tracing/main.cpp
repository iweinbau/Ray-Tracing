#include <iostream>
#include <fstream>
#include <math.h>
#include <algorithm>
#include <list>
#include "vector3f.cpp"
#define PI 3.14159265

using namespace std;

class Material {
public:
	Material() {
		this->diffuseColor = Vect3f();
	}
	Material(Vect3f diffuse,Vect3f specular, float shininess) {
		this->diffuseColor = diffuse;
		this->diffuseFactor = 1;
		this->specularColor = specular;
		this->shininess = shininess;
	}
	Vect3f getDiffuseColor() {
		return diffuseColor * diffuseFactor;
	}
	Vect3f getSpecularColor() {
		return specularColor;
	}
	float getShininess() {
		return shininess;
	}
private:
	float diffuseFactor;
	Vect3f diffuseColor;
	float shininess;
	Vect3f specularColor;

};

class Ray {
public:
	Ray(Vect3f origin, Vect3f direction) {
		this->origin = origin;
		this->direction = direction;
	}
	Vect3f getOrgin() {
		return origin;
	}
	Vect3f getDirection() {
		return direction;
	}
private:
	//the origin point of the ray.
	Vect3f origin;
	//the direction the ray is going.
	Vect3f direction;
};

class Camera {
public:
	//resolution in pixels.
	const int width = 600, height = 600;
	Camera(Vect3f lookfrom, Vect3f lookat, float fov) { // fov is top to bottom in degrees
														//the aspect ration of the image.
		float aspect = width / height;
		//the definition of the up vector of the world.
		Vect3f up(0, 1, 0);
		//fov in radians.
		float theta = fov * PI / 180;
		//half the height of the image view. 
		float half_height = tan(theta / 2);
		//half the width of the image view.
		float half_width = aspect * half_height;
		//the position.
		origin = lookfrom;
		// calculate the direction vector
		n = (lookfrom - lookat).normalized();
		// calculate the horizontal vector of the camera.
		u = up.cross(n).normalized();
		//calculate the up vector.
		v = n.cross(u);
		//  calculate the lower left corner;
		lower_left_corner = origin - u * half_width - v * half_height - n;
		// horizontal vector.
		horizontal = u * half_width * 2;
		//vertical vector.
		vertical = v * 2 * half_height;
	}
	Ray constructRay(int i, int j) {
		//get the pixel size.
		float x = float(i) / float(width);
		float y = float(j) / float(height);
		//calculate the ray.
		return Ray(origin, (lower_left_corner + horizontal * x + vertical * y - origin).normalized());
	}
private:
	//the position of the camera;
	Vect3f origin;
	//the lower left corner of the view plane.
	Vect3f lower_left_corner;
	//the horizontal vector/of the image view.
	Vect3f horizontal;
	//the vertical vector of the image view.
	Vect3f vertical;
	//unit vectors of the camera axis.
	Vect3f u, v, n;
};
class Object {
public:
	Vect3f position;
	virtual bool intersect(Ray ray, Vect3f &intersection, float &t) =0;
	virtual Vect3f getNormalAtPoint(Vect3f) = 0;
	virtual Vect3f getPosition() = 0;
	Material getMaterial() {
		return material;
	}
protected:
	Material material;
};

class Sphere : public Object{
public:
	Sphere(){}
	Sphere(Vect3f position, float radius,Material material){
		this->position = position;
		this->radius = radius;
		this->material = material;
	}
	bool intersect(Ray ray,Vect3f &instersectionPoint,float &t) {
		float t0, t1; // solutions for t if the ray intersects 
					  // analytic solution
		Vect3f L = ray.getOrgin() - position;
		float a = ray.getDirection().dot(ray.getDirection());
		float b = 2 * ray.getDirection().dot(L);
		float c = L.dot(L) - radius;
		if (!solveQuadratic(a, b, c, t0, t1)) return false;

		if (t0 > t1) std::swap(t0, t1);

		if (t0 < 0) {
			t0 = t1; // if t0 is negative, let's use t1 instead 
			if (t0 < 0) return false; // both t0 and t1 are negative 
		}

		t = t0;
		instersectionPoint = ray.getOrgin() + ray.getDirection() * t;

		return true;
	}
	Vect3f getNormalAtPoint(Vect3f point) {
		return (point - position).normalized();
	}
	Vect3f getPosition() {
		return position;
	}
private:
	bool solveQuadratic(const float &a, const float &b, const float &c, float &x0, float &x1)
	{
		float discr = b * b - 4 * a * c;
		if (discr < 0) return false;
		else if (discr == 0) {
			x0 = x1 = -0.5 * b / a;
		}
		else {
			float q = (b > 0) ?
				-0.5 * (b + sqrt(discr)) :
				-0.5 * (b - sqrt(discr));
			x0 = q / a;
			x1 = c / q;
		}

		return true;
	}
	float radius;
};
class Light {
	public:
		Light(Vect3f diffuse, Vect3f specular, Vect3f position) {
			this->diffuse = diffuse;
			this->specular = specular;
			this->position = position;
		}
		Vect3f getPosition() {
			return position;
		}
		Vect3f getDiffuse() {
			return diffuse;
		}
		Vect3f getSpecular() {
			return specular;
		}
	private:
		Vect3f specular;
		Vect3f diffuse;
		Vect3f position;

};
void save_to_file(char *filename, int width, int height, Vect3f *pixels)
{
	// save frame buffer to file
	std::ofstream ofs;
	ofs.open("./out.ppm", std::ios::out | std::ios::binary);
	ofs << "P6\n" << width << " " << height << "\n255\n";
	for (int i = 0; i < height * width; ++i) {
		ofs << (unsigned char)(min(max(pixels[i].getX(),0.0f), 1.0f)  * 255) <<
			   (unsigned char)(min(max(pixels[i].getY(), 0.0f), 1.0f) * 255) <<
			   (unsigned char)(min(max(pixels[i].getZ(), 0.0f), 1.0f) * 255);
	}

	ofs.close();
}


int main() {
	cout << "Basic Ray tracing!\n";

	//construct a camera 
	Vect3f lookfrom = Vect3f(5, 7, 0);
	Vect3f lookat = Vect3f(0, 0, 0);
	Camera camera(lookfrom, lookat, 45);

	//image setup
	const int size = camera.width * camera.height;
	Vect3f* pixels = new Vect3f[size];

	//World setup
	Light light = Light(Vect3f(1, 1, 0),Vect3f(1,1,1) , Vect3f(5, 2, 0));

	Sphere sphere = Sphere(Vect3f(0, 0, 0), 3, Material(Vect3f(1, 0, 0),Vect3f(1,1,1),50));
	Sphere sphere2 = Sphere(Vect3f(0, 0, 3), 0.5, Material(Vect3f(0, 1, 0),Vect3f(1,1,1),50) );

	//create objects.
	list<Object*> objects;
	objects.push_back(&sphere);
	objects.push_back(&sphere2);

	//create lights.
	list<Light*> lights;
	lights.push_back(&light);


	int x, y;
	int index = 0;
	for (x = 0; x < camera.width; x++){
		for (y = 0; y < camera.height; y++){
			//construct a ray for through this pixel.
			Ray ray = camera.constructRay(x, y);
			//initialization for the trace;
			float tnear = INFINITY;
			Object* closest = NULL;
			Vect3f* intersection = &Vect3f();
			//flag true when we hit something from this ray.
			bool hit = false;
			//for each object find intersection
			//construct ray
			for each (Object* obj in objects)
			{	
				//current intersection;
				float t;
				if ((*obj).intersect(ray, *intersection,t)) {
					hit = true;
					if (t <= tnear) {
						//we found a closer object.
						closest = obj;
						tnear = t;
					}
				}
			}
			if (hit) {
				//We hit something calculate the color of the pixel.
				//TODO: add shadow ray,reflection ray, refraction ray and support multiple depths.
				//TODO: add specular light.
				//TODO: add ambient light.
				//TODO: maybe create texture mapping?
				Vect3f color = Vect3f();
				//get the surface normal at the point.
				Vect3f normal = (*closest).getNormalAtPoint((*intersection));
				for each (Light* l in lights)
				{
					//******** Diffuse *********\\
					//get the light direction.
					Vect3f lightDir = ((*l).getPosition() - *intersection).normalized();
					//calculate diffuse intensity.
					float intensity = max((float)0, lightDir.dot(normal));
					Vect3f diffuseColor = (*closest).getMaterial().getDiffuseColor() * intensity * (*l).getDiffuse();
					//******* Specular *********\\
					//R_i - 2 N (R_i . N)
					Vect3f reflectedLightvector = ((normal * 2 * lightDir.dot(normal)) - lightDir).normalized();
					Vect3f viewDir = ray.getDirection().neg();
					Vect3f specularColor = (*closest).getMaterial().getSpecularColor() * (*l).getSpecular() * pow(reflectedLightvector.dot(viewDir),(*closest).getMaterial().getShininess());
					//calculate the pixel color.
					color = color + diffuseColor + specularColor;
				}
				pixels[index++] = color;
			}
			else {
				//no hit just set the background color;
				pixels[index++] = Vect3f();
			}
		}
	}

	save_to_file("test.bmp", camera.width, camera.height, pixels);

	return 0;
}
