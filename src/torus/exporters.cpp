
#include "exporters.h"
#include "graph.h"

#include <string>
#include <iostream>
#include <fstream>
using namespace std;


void exporters::LineList::export(string filename,vector<Ogre::Vector3> vertexlist,vector<Index2> indices) {

	ofstream myfile (filename.c_str());
	if (myfile.is_open())
	{
		myfile<<vertexlist.size()<<endl;
		myfile<<indices.size()<<endl;

		for (vector<Ogre::Vector3>::iterator it = vertexlist.begin();it!=vertexlist.end();++it) {
			myfile<<it->x<<"\t"<<it->y<<"\t"<<it->z<<endl;
		}

		for (vector<Index2>::iterator it = indices.begin();it != indices.end(); ++it) {
			myfile<<it->i1<<"\t"<<it->i2<<endl;	
		}
	    myfile.close();
	} 
	else cout << "Unable to open file";
  
}

void exporters::Passage::export(string filename,vector<Ogre::Vector3> vertexlist,vector<Index2> indices,std::vector<CaveOffset> offsets) {
	ofstream myfile (filename.c_str());
	if (myfile.is_open())
	{
		myfile<<vertexlist.size()<<endl;
		
		for (vector<Ogre::Vector3>::iterator it = vertexlist.begin();it != vertexlist.end(); ++it) {
			myfile<<it->x<<"\t"<<it->y<<"\t"<<it->z<<endl;	
		}
		Graph g;
		g.create(indices,vertexlist.size());
		g.print(myfile,'\t',0,offsets);
	    myfile.close();
	} 
	else cout << "Unable to open file";
  
}

