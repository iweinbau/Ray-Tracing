#include "math.h"

class Vect3f {
private:
	float x;
	float y;
	float z;

public:
	Vect3f()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	Vect3f(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	float getX() { return x; }
	float getY() { return y; }
	float getZ() { return z; }

	float length() {
		return sqrt((x * x) + (y * y) + (z * z));
	}

	Vect3f normalized() {
		float mag = length();

		return Vect3f(x / mag, y / mag, z / mag);
	}

	Vect3f neg() {
		return Vect3f(-x, -y, -z);
	}

	float dot(Vect3f other) {
		return x * other.getX() + y * other.getY() + z * other.getZ();
	}

	Vect3f cross(Vect3f other) {
		float x_ = y * other.getZ() - z * other.getY();
		float y_ = z * other.getX() - x * other.getZ();
		float z_ = x * other.getY() - y * other.getX();

		return Vect3f(x_, y_, z_);
	}

	Vect3f operator + (const Vect3f &other) {
		return Vect3f(x + other.x, y + other.y, z + other.z);
	}

	Vect3f operator - (const Vect3f &other) {
		return Vect3f(x - other.x, y - other.y, z - other.z);
	}

	Vect3f operator * (const Vect3f &other) {
		return Vect3f(x * other.x, y * other.y, z * other.z);
	}

	Vect3f operator * (const float &other) {
		return Vect3f(x * other, y * other, z * other);
	}

	Vect3f operator / (const Vect3f &other) {
		return Vect3f(x / other.x, y / other.y, z / other.z);
	}
};

