#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <hash_map>
#include <math.h>
#include "base.h"
#include <OgreMath.h>


using namespace std;

namespace importers {
	class PolygonImporter
	{
		public:
			static void import(string filename,stdext::hash_map<const std::string, Ogre::Vector3> &vertexlist,std::vector<Index2Str> &indices);

	};

	class PlotImporter {
		public:
			static void import(std::string filename, std::vector<Ogre::Vector3> &vertexlist, std::vector<Index2> &indices,std::vector<CaveOffset> &offsets);	
	};

	class SurvexImporter
	{
		public:
			static void import(std::string filename, std::vector<Ogre::Vector3> &vertexlist, std::vector<Index2> &indices);	

	};


}
