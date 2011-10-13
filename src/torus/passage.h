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

class SourcePoint : public EndPoint {
public :
	SourcePoint(double x, double y, double z):EndPoint(x,y,z) { };
	SourcePoint():EndPoint(0,0,0) { };
	std::vector<EndPoint> points;	
};



class Passage {
public:
	std::vector<SourcePoint> points;
	void load(const char* pFilename);
};


#endif