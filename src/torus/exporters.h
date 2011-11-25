#include "base.h"

namespace exporters {
	class LineList
	{
		public:
			static void export(string filename,std::vector<Ogre::Vector3> vertexlist,std::vector<Index2> indices);
	};

	class Passage
	{
		public:
			static void export(string filename,std::vector<Ogre::Vector3> vertexlist,std::vector<Index2> indices, std::vector<CaveOffset> offsets);
	};



}
