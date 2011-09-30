#include <hash_map>
#include <list>
#include "base.h"
#include <vector>
#include <fstream>

class Graph
{
	public:
		void create(std::vector<Index2> indices,int vertn);
		void print(std::ostream &stream,char separator,int startindex, std::vector<CaveOffset> offsets);
	private:
		stdext::hash_map<int,std::list<int>> adjlist;
		int globalsize;
		
};
