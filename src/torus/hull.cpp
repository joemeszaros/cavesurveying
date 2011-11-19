#include<windows.h>
#include "point.h"
#include "util/mathutil.h"
#include "passage.h"
#include "util/meshutil.h"
#include "OgreManualObject.h"
#include "OgreSceneManager.h"

using namespace simplex;

class Hull {
public:
	Ogre::ManualObject* manual;
	Vector* referencevector;
	int limit,cnt;
	simplex::Plane plane;


	Hull():manual(0) {
		referencevector = NULL;
	}

	simplex::Plane getPlane() {
		return plane;
	}

	void getTracks(SourcePoint sourcefrom, SourcePoint sourceto, std::vector<Vector> tracks[],double perimeters[], Vector finalintersections[], Vector pivotpoints[]) {

		Vector from, to;
		Vector n, reference, randomvector;
		
		from = sourcefrom;
		to = sourceto;

		SourcePoint sourcepoints[2] = { sourcefrom, sourceto};

		
		for (int p=0;p<2;p++) {
			pivotpoints[p] = util::Mesh::getPivotPoint(sourcepoints[p].points);
		}
		n = (pivotpoints[1]-pivotpoints[0]).normalize();
		
		//addtoManual2(from, from + n*0.4, Ogre::ColourValue(0,1.0,0));
		//addtoManual2(Vector(0,0,0),  n, Ogre::ColourValue(0,1.0,0));
		
		if (referencevector == 0) {
		
			//create random vector
			double minvalue = 1.0;
			if (abs(n.x) < minvalue) { minvalue = n.x; randomvector = Vector(1,0,0); }
			if (abs(n.y) < minvalue) { minvalue = n.y; randomvector = Vector(0,1,0); }
			if (abs(n.z) < minvalue) { minvalue = n.z; randomvector = Vector(0,0,1); }
			
			reference = n.cross(randomvector);
			reference = reference.normalize();
			referencevector = new Vector(reference);
		} else {
			reference = *referencevector;
		}

				

		//addtoManual2(from+n*0.4, from+n*0.4+ reference*0.6 ,Ogre::ColourValue(0,0,1.0));

		double idistance = -1.0, crossresult, dist;
		Vector intersection;

		double finalloopcounters[2];
		double subtract = 0,t = 0;
		bool predicate = false;

		std::vector<Vector> visitedstations[2];

		for	(int index = 0; index < 2; index++) {
			perimeters[index] = 0;
		}
		

		int previ = 0,i = 0, loopcounter = 0;
		Vector prevcirclepoint,circlepoint ;
		
		Vector crossproduct = n.cross(reference).normalize();

		SourcePoint sourcefrom_loop = sourcefrom.copy();
		sourcefrom_loop.points.push_back(sourcefrom.points.at(0));
		SourcePoint sourceto_loop = sourceto.copy();
		sourceto_loop.points.push_back(sourceto.points.at(0));
		SourcePoint sourcepoints_loop[2] = {sourcefrom_loop, sourceto_loop};

		
		

		for(int j=0; j<2;j++) {

			loopcounter = 0;
			idistance = -1.0;	
			Vector pivotpoint =  pivotpoints[j];
			//pivotpoints[j] = pivotpoint;

			

			if (j == 0) {
				double l = n.length();
				plane = simplex::Plane(reference, n* pivotpoint.dot(reference),n);
			}
			int round = 0;

			for(std::vector<EndPoint>::iterator it = sourcepoints_loop[j].points.begin(); it != sourcepoints_loop[j].points.end();++it) {
				circlepoint = *it;
				
				//if (round < 2) {
				//addtoManual2(circlepoint, circlepoint- Vector(0.3,0.3,0.3)*round *(j ==0 ? -1 : 1), Ogre::ColourValue::Blue);
				//}
				i = util::Math::getPlaneSignum(pivotpoint, reference, circlepoint);
				std::stringstream ss;
				//ss<< "j : " << j << "signum : " << i << endl;
				//ss<< "current id :" << it->Id <<endl;
				//debug(ss.str().c_str());

				if (loopcounter != 0 && (previ * i != 1)) {
					
					if (i * previ == 0 && (i+previ) == 0) { //2 on the plane
						predicate = (prevcirclepoint-pivotpoint).length() > (circlepoint-pivotpoint).length();
						intersection =  predicate ? prevcirclepoint : circlepoint;
						subtract = (predicate ? 1.0 : 0);
					} else if (i * previ == 0 && (i+previ) != 0) { // 1 on the plane
						intersection = (i == 0 ? circlepoint : prevcirclepoint);
						subtract = (i == 0 ? 0 : 1 );
					} else if (i * previ == -1) { // 0 on the plane
						intersection = util::Math::getIntersection(prevcirclepoint, circlepoint, pivotpoint, reference);
						subtract = 0.5;
					} 
					dist = (intersection - pivotpoint).length();
					if (util::Math::getPlaneSignum(pivotpoint,crossproduct, intersection) >= 0) {
							dist = (intersection - pivotpoint).length();
							if (dist > idistance){
								finalintersections[j] = intersection;
								idistance = dist;
								finalloopcounters[j] = loopcounter-subtract;
							}
						}
				}
				
				previ = i;
				prevcirclepoint = circlepoint;
				std::stringstream ss2;
				//ss<< "j : " << j << "signum : " << i << endl;
				//ss2<< "prev point:" << prevcirclepoint.toString() <<endl;
				//debug(ss2.str().c_str());
				loopcounter++;
				subtract = 0;
				round++;
			}
			
			tracks[j].push_back(finalintersections[j]);
			//addtoManual2(finalintersections[j],finalintersections[j] -n*0.4,Ogre::ColourValue(0,1,1));
			
		}

		Vector first;

		for(int j=0; j<2;j++) {
			loopcounter = 0;
			
			for(std::vector<EndPoint>::iterator it = sourcepoints[j].points.begin(); it != sourcepoints[j].points.end();++it) {
				circlepoint = *it;

				if (loopcounter != 0) {
					perimeters[j] += (circlepoint-prevcirclepoint).length();
				} else {
					first = circlepoint;
				}

				if (loopcounter < finalloopcounters[j]) {
					visitedstations[j].push_back(circlepoint);
				} else if (loopcounter > finalloopcounters[j]) {
					tracks[j].push_back(circlepoint);
				}

				prevcirclepoint = circlepoint;
				loopcounter++;
			}

			perimeters[j] += (first-circlepoint).length();

			for(std::vector<Vector>::iterator it = visitedstations[j].begin(); it != visitedstations[j].end();++it) {
				tracks[j].push_back(*it);
			}

			tracks[j].push_back(finalintersections[j]);

		}



	}



	void jointTracks(std::vector<Vector> tracks[], Vector finalintersections[], Vector sourcepoints[], double perimeters[]) {
		

		Vector runners[2];
		Vector nexpoints[2];
		double runneddistance[2];

		for	(int index = 0; index < 2; index++) {
			runneddistance[index] = 0;
		}
		

		std::vector<Vector>::iterator it[2];
		for(int j=0; j<2;j++) {
			it[j] = tracks[j].begin();
			
			runners[j] = *it[j];
			++(it[j]);
			nexpoints[j] = *it[j];
		}

		//addtoManual(runners[0],runners[1],(runners[0]-sourcepoints[0]).normalize(), (runners[1]-sourcepoints[1]).normalize(), ,Ogre::ColourValue(0,0,1),0.0, 0.0);
		addtoManual3(runners[0],runners[1],(runners[0]-sourcepoints[0]).normalize(), (runners[1]-sourcepoints[1]).normalize(), Ogre::ColourValue(0,0,1),0.0, 0.0);

		double ratio[2];
		int faster = 0;
		int slower = 0;
		int cnt = 0;
		double l = 0;
		int cnts[2] = { 2 , 2};
		int cc = 0;
		
		Vector prevrunners[2] = { runners[0], runners[1] };
		Vector prevnormals[2] = { (runners[0]-sourcepoints[0]).normalize(), (runners[1]-sourcepoints[1]).normalize() };
		double prevucoords[2] = { 0 ,0 };
		
		while (runneddistance[0] + runneddistance[1] <= (perimeters[0] + perimeters[1])*1.0f ) { // && it[0] !=tracks[0].end() && it[1] !=tracks[1].end()) {

			cnt++;

			if (cnt > limit) {
				return;
			}

			cc++;
			if (cc > 150) break;

			cnt++;
			for(int j=0; j<2;j++) {
				l = (nexpoints[j]-runners[j]).length();
 				ratio[j] = (runneddistance[j] + l) / perimeters[j];
			}

			if (ratio[1] > ratio[0]) {
				faster = 1; slower = 0;
			} else if (ratio[1] < ratio[0]) {
				faster = 0; slower = 1;
			} else {
				faster = -1; slower = -1;
			}

			if (faster * slower == 0) { //not in the same point
				double inner = ratio[slower] * perimeters[faster];
				double before = inner - runneddistance[faster];
				l = (nexpoints[faster]-runners[faster]).length();
				double m = before / l;
				runneddistance[slower] += (nexpoints[slower] - runners[slower]).length();
				runners[slower] = nexpoints[slower];
				if (cnts[slower] < tracks[slower].size()) {
					++(it[slower]);
					cnts[slower]++;
					nexpoints[slower] = *it[slower];
				}
				double added = ((nexpoints[faster]-runners[faster]) * m).length();

				runners[faster] = runners[faster] + (nexpoints[faster]-runners[faster]) * m;
				
				runneddistance[faster] += added;
				
			} else if (faster * slower < 0) {
				for(int j=0; j<2;j++) {
					runners[j] = nexpoints[j];
					++(it[j]);
					nexpoints[j] = *it[j];
				}
				
				
				
				
			}
			double u1 = runneddistance[0]/perimeters[0];
			double u2 = runneddistance[1]/perimeters[1];
			addtoManual(runners[0],runners[1],(runners[0]-sourcepoints[0]).normalize(), (runners[1]-sourcepoints[1]).normalize(), prevrunners[0], prevrunners[1], prevnormals[0], prevnormals[1] ,Ogre::ColourValue(0.7,0.7,0,0.5), u1, u2, prevucoords[0], prevucoords[1]);
			addtoManual3(runners[0],runners[1],(runners[0]-sourcepoints[0]).normalize(), (runners[1]-sourcepoints[1]).normalize(), Ogre::ColourValue(0.7,0.7,0,0.5), u1, u2);
			for (int i = 0; i <2; i++) {
				prevrunners[i] = runners[i];
				prevnormals[i] = (runners[i]-sourcepoints[i]).normalize();
				prevucoords[0] = u1;
				prevucoords[1] = u2;
			}
			
			if (finalintersections[0] == nexpoints[0] && finalintersections[1] == nexpoints[1]) {
				runneddistance[0] += (nexpoints[0] - runners[0]).length();
				runneddistance[1] += (nexpoints[1] - runners[1]).length();
				addtoManual(nexpoints[0],nexpoints[1],(nexpoints[0]-sourcepoints[0]).normalize(), (nexpoints[1]-sourcepoints[1]).normalize(), prevrunners[0], prevrunners[1], prevnormals[0], prevnormals[1] ,Ogre::ColourValue(0.7,0.7,0,0.5), u1, u2, prevucoords[0], prevucoords[1]);
				addtoManual3(nexpoints[0],nexpoints[1],(nexpoints[0]-sourcepoints[0]).normalize(), (nexpoints[1]-sourcepoints[1]).normalize(),Ogre::ColourValue(0,0,1,0.5), 1.0, 1.0);

				break;
			}

		}
	}


	
	Ogre::ManualObject* createHull(Passage p, Ogre::SceneManager * mScrMgr,Ogre::String manualName, Ogre::String materialName) {

		cnt = 0;

		createManualObject(mScrMgr, manualName, materialName);

		int available = p.points.size()-1;

		for (std::vector<SourcePoint>::iterator it = p.points.begin(); available > 0; )
		{
			cnt++;
			double perimeters[2];
			Vector finalintersections[2];
			std::vector<Vector> tracks[2];
			Vector pivotpoints[2];
			SourcePoint p1 = *it;
			++it;
			available --;
			SourcePoint p2 = *it;


			getTracks(p1,p2, tracks, perimeters, finalintersections,pivotpoints);

			std::stringstream ss;
			ss << "round : " << cnt << " intersections: "<<endl << finalintersections[0].toString() << endl << finalintersections[1].toString() << endl << " pivotpoints: "<<endl << pivotpoints[0].toString() << endl << pivotpoints[1].toString() << endl;;
			debug(ss.str().c_str());
			jointTracks(tracks, finalintersections, pivotpoints, perimeters);
			
		}

		manual->end();
		return manual;
	}
private:
	void createManualObject(Ogre::SceneManager *mSceneMgr, Ogre::String name,Ogre::String materialname) {
		manual = mSceneMgr->createManualObject(name);
		manual->setDynamic(true);
		manual->begin(materialname, Ogre::RenderOperation::OT_TRIANGLE_STRIP);
	}

	void addtoManual3(Vector p1, Vector p2, Vector n1, Vector n2,Ogre::ColourValue color, double u1, double u2) {
		manual->position(p1.x,p1.y,p1.z);
 		manual->normal(n1.x, n1.y, n1.z);
 		manual->colour(color);
 		manual->textureCoord(0.0,u1);

 		manual->position(p2.x,p2.y,p2.z);
 		manual->normal(n2.x,n2.y,n2.z);
 		manual->colour(color);
 		manual->textureCoord(1.0,u2);
	}

	void addtoManual(Vector p1, Vector p2, Vector n1, Vector n2, Vector prev_p1, Vector prev_p2, Vector prev_n1, Vector prev_n2, Ogre::ColourValue color, double u1, double u2, double prev_u1, double prev_u2) {

		manual->position(prev_p1.x,prev_p1.y,prev_p1.z);
		manual->normal(prev_n1.x, prev_n1.y, prev_n1.z);
		manual->colour(color);
		manual->textureCoord(0.0,prev_u1);

		manual->position(prev_p2.x,prev_p2.y,prev_p2.z);
		manual->normal(prev_n2.x, prev_n2.y, prev_n2.z);
		manual->colour(color);
		manual->textureCoord(1.0,prev_u2);

		manual->position(p1.x,p1.y,p1.z);
		manual->normal(n1.x, n1.y, n1.z);
		manual->colour(color);
		manual->textureCoord(0.0,u1);

		manual->position(prev_p2.x,prev_p2.y,prev_p2.z);
		manual->normal(prev_n2.x, prev_n2.y, prev_n2.z);
		manual->colour(color);
		manual->textureCoord(1.0,prev_u2);

		manual->position(p1.x,p1.y,p1.z);
		manual->normal(n1.x, n1.y, n1.z);
		manual->colour(color);
		manual->textureCoord(0.0,u1);

		manual->position(p2.x,p2.y,p2.z);
		manual->normal(n2.x,n2.y,n2.z);
		manual->colour(color);
		manual->textureCoord(1.0,u2);
	}


	 void addtoManual2(Vector p1, Vector p2, Ogre::ColourValue color) {
 			manual->position(p1.x,p1.y,p1.z);
 			manual->colour(color);
 			manual->position(p2.x,p2.y,p2.z);
 			manual->colour(color);
	 }

	void debug(const char * s) {
		OutputDebugString(s);
		
	}

};