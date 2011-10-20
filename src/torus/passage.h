#include <stdio.h>
#include "tinyxml.h"

#include <iostream>
#include <vector>
#include <time.h>


#include <stdlib.h>
#include "point.h"
#include "util/util.h"

#ifndef PASSAGE_H
#define PASSAGE_H

using namespace std;
using namespace simplex;

class EndPoint : public Vector {
public:
	std::string Id;
	EndPoint(double x,double y,double z, std::string Id = "undefined"):Vector(x,y,z),Id(Id) {  };
	
};

class SourcePoint : public EndPoint {
public :
	SourcePoint(double x, double y, double z, std::string Id = "undefined"):EndPoint(x,y,z,Id) { };
	SourcePoint():EndPoint(0,0,0) { };
	std::vector<EndPoint> points;	
};



class Passage {
public:
	std::vector<SourcePoint> points;
	void load(const char* pFilename);
};


#endif