#include "importers.h"
#include "exporters.h"
#include "windows.h"

void test() {

	std::vector<Index2> indices;
	std::vector<Ogre::Vector3> vertexlist;

	std::vector<Index2> indices2;
	std::vector<Ogre::Vector3> vertexlist2;

	std::vector<CaveOffset> offsets;
	
	//importers::PolygonImporter::import("c:\\Program Files\\POLYGON2.7\\CaveData\\Samples\\Vecsem.cave",vertexlist,indices);

	formats::Plot::import("d:\\tmp\\önlab\\besz\\Eglwys.plt",vertexlist,indices,offsets);

	//importers::SurvexImporter::import("d:\\tmp\\önlab\\files\\exorted\\Eglwys.3d",vertexlist,indices);

	formats::Passage4::export("d:\\tmp\\önlab\\besz\\eglwys.passage",vertexlist,indices,offsets);

}




	INT WINAPI WinMain22( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
	{
		test();
		return 0;
	}
