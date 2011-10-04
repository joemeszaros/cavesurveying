#include <math.h>
#ifndef POINT_H
#define POINT_H

class Point {
public :
	double x;   // x coordinate
	double y;   // y coordinate
	double z;
	
	Point() {
		x = 0; y = 0; z = 0;
	}
	Point(double _x,double _y, double _z) {
		x = _x;
		y = _y;
		z = _z;
	}

	Point operator+(Point &p) {
		return Point(x+p.x,y+p.y,z+p.z);
	}

	Point operator-(Point &p) {
		return Point(x-p.x,y-p.y,z-p.z);
	}

	Point operator/(double per) {
		return Point(x/per,y/per,z/per);
	}
	
	Point operator*(double per) {
		return Point(x*per,y*per,z*per);
	}

	bool operator==(Point &p) {
		return (x == p.x && y == p.y && z == p.z);
	}

	double length() {
		return sqrtl(x*x+y*y+z*z);
	}

	double dot(Point &p) {
		return x*p.x+y*p.y+z*p.z;
	}

	Point cross(Point &p) {
		return Point(y*p.z-z*p.y,z*p.x-x*p.z,x*p.y-y*p.x);
	}

	Point normalize() {
		double l = sqrtl(x*x+y*y+z*z);
		return Point(x/l,y/l,z/l);
	}

};



struct Index {
	int x;  
	int y;  
	int z;    
	Index(int _x,int _y, int _z) {
		x = _x;
		y = _y;
		z = _z;
	}
};

#endif