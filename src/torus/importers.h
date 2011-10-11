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
#include "passage.h"


using namespace std;

namespace formats {

	class Polygon
	{
		public:
			static void import(string filename,stdext::hash_map<const std::string, Ogre::Vector3> &vertexlist,std::vector<Index2Str> &indices);

	};

	class Therion
	{
		public:
			static void import(string filename,stdext::hash_map<const std::string, Ogre::Vector3> &vertexlist,std::vector<Index2Str> &indices);
			static Passage toPassage(stdext::hash_map<const std::string, Ogre::Vector3> &vertexlist,std::vector<Index2Str> &indices);

	};

	class Plot {
		public:
			static void import(std::string filename, std::vector<Ogre::Vector3> &vertexlist, std::vector<Index2> &indices,std::vector<CaveOffset> &offsets);	
	};

	class Survex
	{
		public:
			static void import(std::string filename, std::vector<Ogre::Vector3> &vertexlist, std::vector<Index2> &indices);	

	};

	class LineList
	{
		public:
			static void export(string filename,std::vector<Ogre::Vector3> vertexlist,std::vector<Index2> indices);
	};

	class Passage4
	{
		public:
			static void export(string filename,std::vector<Ogre::Vector3> vertexlist,std::vector<Index2> indices, std::vector<CaveOffset> offsets);
	};


}
