#include <math.h>
#include <OgreVector3.h>

#ifndef POINT_H
#define POINT_H

namespace simplex {
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

		Vector operator -() {
			return Vector(-x,-y,-z);
		}

		Vector normalize() {
			double l = sqrtl(x*x+y*y+z*z);
			return Vector(x/l,y/l,z/l);
		}

		Ogre::Vector3 toOgreVector() {
			return Ogre::Vector3(x, y, z);
		}

	};


	class Plane {

	public:
		Vector normal;
		Vector point;


		Plane() : normal(Vector(0,0,0)),point(Vector(0,0,0)) {}

		Plane(double a, double b, double c, double d)  {
			normal = Vector(a,b,c);
			double t = -d / (a*a + b*b + c*c);
			point = normal * t;
		}
		
		Plane(Vector &normal, Vector &point) {
			this->normal = normal;
			this->point = point;
		}

		double* getParameters() {
			double *p = new double[4];
			p[0] = normal.x;
			p[1] = normal.y;
			p[2] = normal.z;
			p[3] =  0 - point.dot(normal);
			return p;
		}

		double distanceFromOrigo() {
			return 0-point.length();
		}
		
	};
}

#endif