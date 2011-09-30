#include <string>
#include <OgreVector3.h>

#ifndef BASE_H
#define BASE_H
 
using namespace std;

/*struct Point {
    double x;   // x coordinate
    double y;   // y coordinate
	double z;    
	Point(double _x,double _y, double _z) {
		x = _x;
		y = _y;
		z = _z;
	}

	Point() : x(0),y(0),z(0) {}
}; */

struct Index2Str {
	string i1;
	string i2;
	
	Index2Str(string _i1,string _i2) {
		i1 = _i1;
		i2 = _i2;
	}
};

struct Index2 {
	unsigned long i1;
	unsigned long i2;
	
	Index2(unsigned long _i1,unsigned long _i2) {
		i1 = _i1;
		i2 = _i2;
	}
};

struct BPoint {	
	Ogre::Vector3  p;
	bool contains;
	BPoint(Ogre::Vector3 _p, bool _c) {
		p = _p;
		contains = _c;
	}

	BPoint() : p(0,0,0),contains(false) {}
};

struct CaveOffset {
	double o1,o2,o3,o4;
	CaveOffset(double _o1,double _o2,double _o3,double _o4) : o1(_o1),o2(_o2),o3(_o3),o4(_o4) {}
	CaveOffset() :o1(0),o2(0),o3(0),o4(0) {}
};

struct CaveCoord
    {
	public :
        double Length;
        double Azimuth;
        double Vertical;
		CaveCoord(double h, double i, double l)
        {
            Length = h;
            Azimuth = i;
            Vertical = l;
        }

		CaveCoord() : Length(0),Azimuth(0), Vertical(0)	{}

    };
#endif