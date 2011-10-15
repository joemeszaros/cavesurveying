#include <math.h>
#ifndef POINT_H
#define POINT_H

class Vector {
public :
	double x;  
	double y;   
	double z;
	
	Vector() {
		x = 0; y = 0; z = 0;
	}
	Vector(double _x,double _y, double _z) {
		x = _x;
		y = _y;
		z = _z;
	}

	Vector operator+(Vector &p) {
		return Vector(x+p.x,y+p.y,z+p.z);
	}

	void operator+=(Vector &p) {
		x+=p.x;
		y+=p.y;
		z+=p.z;
	}

	Vector operator-(Vector &p) {
		return Vector(x-p.x,y-p.y,z-p.z);
	}

	Vector operator/(double per) {
		return Vector(x/per,y/per,z/per);
	}

	void operator/=(double per) {
		x = x/per;
		y = y/per;
		z = z/per;
	}
	
	
	Vector operator*(double per) {
		return Vector(x*per,y*per,z*per);
	}

	bool operator==(Vector &p) {
		return (x == p.x && y == p.y && z == p.z);
	}

	double length() {
		return sqrtl(x*x+y*y+z*z);
	}

	double dot(Vector &p) {
		return x*p.x+y*p.y+z*p.z;
	}

	Vector cross(Vector &p) {
		return Vector(y*p.z-z*p.y,z*p.x-x*p.z,x*p.y-y*p.x);
	}

	Vector normalize() {
		double l = sqrtl(x*x+y*y+z*z);
		return Vector(x/l,y/l,z/l);
	}

};


#endif