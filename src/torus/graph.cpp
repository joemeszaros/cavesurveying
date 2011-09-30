
#include "graph.h"

void Graph::create(vector<Index2> indices,int vertn) {

	this->globalsize = vertn;

	for (vector<Index2>::iterator it = indices.begin();it != indices.end();++it) {
		adjlist[it->i1].push_back(it->i2);
	}
}

void Graph::print(std::ostream &stream,char separator,int startindex,std::vector<CaveOffset> offsets) {
	stdext::hash_map<int,std::list<int>>::const_iterator iter;
	bool withoffset = true;
	int closed = 0;
	int *closelist = new int[this->globalsize];
	int *visited = new int[this->globalsize];

	srand ( time(NULL) );

	for (int i = 0; i < this->globalsize;i++) 
	{ 
		visited[i] = 0;
		iter = adjlist.find(i);
	
		if ( iter != adjlist.end() && adjlist[i].size() > 0) {
			closelist[i] = 0; 
		} else if (iter == adjlist.end() || adjlist[i].size() == 0) {
			closelist[i] = 1;
			closed++;
		}
		
	}

	int act = startindex;
	stringstream line;
	int t,listsize = 0;
	CaveOffset of;
	double actoffset = 1.6;
	while (closed < this->globalsize) {

		if (withoffset) {
			of = offsets[act];
			
			double delta = (rand() % 10 + 1) / 3.0;
			int sign = rand() % 2 - 1;
			actoffset = actoffset + sign * delta;
			if (actoffset <0) {
				actoffset = -1 * actoffset;
			}
			double deffoffset = 0;
			line << act <<","<<(of.o1==0?deffoffset:of.o1)<<";"<<(of.o2==0?deffoffset:of.o2)<<";"<<(of.o3==0?deffoffset:of.o3)<<";"<<(of.o4==0?deffoffset:of.o4);
			//line << act <<","<<actoffset<<";"<<actoffset<<";"<<actoffset<<";"<<actoffset;
		} else line << act;
		//stream << act;
		visited[act] = 1;

		if (closelist[act] == 0) {
			//cout<<separator;
			line << separator;
			listsize++;
			t = act;
			act = adjlist[act].front();
			adjlist[t].pop_front();
			if (adjlist[t].size() == 0) {
				closelist[t] = 1;
				closed++;
			}
		} else {
			
			stream << ++listsize << separator << line.str() << endl;
			actoffset = 2.4 / (rand() % 10 + 1);
			listsize = 0;
			act = -1;
			line.str("");
			
			for (int i = 0;i < this->globalsize;i++) {
				if (closelist[i] == 0 && visited[i] == 1) { act = i; break;};
			}
			if (act == -1) 
			{
				for (int i = 0;i < this->globalsize;i++) {
					if (closelist[i] == 0) { act = i; break;};
				}
			}	

		}

	}

	stream << listsize << separator << line.str() << endl;
	
}