#include <stdio.h>
#include "tinyxml.h"

#include <iostream>
#include <vector>
#include <time.h>


#include <stdlib.h>
#include "point.h"

#ifndef PASSAGE_H
#define PASSAGE_H

using namespace std;

class BasePoint {

public :
	double x;
	double y;
	double z;
	Point toPoint() { return Point(x,y,z); };
	BasePoint(double x, double y, double z) : x(x),y(y),z(z) {}
};

class SourcePoint : public BasePoint {
public :
	SourcePoint(double x, double y, double z):BasePoint(x,y,z) { };
	SourcePoint():BasePoint(0,0,0) { };
	std::vector<BasePoint> points;	
};



class Passage {
public:
	std::vector<SourcePoint> points;
	void load(const char* pFilename);
};


#endif