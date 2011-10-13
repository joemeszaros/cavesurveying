#include<windows.h>
#include "point.h"
#include "util/mathutil.h"
#include "passage.h"
#include "util/meshutil.h"
#include "OgreManualObject.h"
#include "OgreSceneManager.h"

using namespace Ogre;

class Hull {
public:
	ManualObject* manual;

	void getTracks(SourcePoint sourcefrom, SourcePoint sourceto, std::vector<Vector> tracks[],double perimeters[], Vector finalintersections[], Vector pivotpoints[]) {

		Vector from, to;
		Vector n, reference, randomvector;
		
		from = sourcefrom;
		to = sourceto;

		SourcePoint sourcepoints[2] = {sourcefrom, sourceto};

		n = (to-from).normalize();
		
		//addtoManual(from, from + n, Ogre::ColourValue(0.6,0.6,1));
		//addtoManual(Vector(0,0,0),Vector(-10,3,3),Ogre::ColourValue(1,1,0));

		//create random vector
		double minvalue = 1.0;
		if (abs(n.x) < minvalue) { minvalue = n.x; randomvector = Vector(1,0,0); }
		if (abs(n.y) < minvalue) { minvalue = n.y; randomvector = Vector(0,1,0); }
		if (abs(n.z) < minvalue) { minvalue = n.z; randomvector = Vector(0,0,1); }

		reference = n.cross(randomvector);
		reference = reference.normalize();
		//addtoManual(from+n, from+n + reference ,Ogre::ColourValue(0,1,1));

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

		for(int j=0; j<2;j++) {

			loopcounter = 0;
			idistance = -1.0;
			Vector pivotpoint =  util::Mesh::getPivotPoint(sourcepoints[j].points);
			pivotpoints[j] = pivotpoint;

			for(std::vector<EndPoint>::iterator it = sourcepoints[j].points.begin(); it != sourcepoints[j].points.end();++it) {
				circlepoint = *it;

				i = util::Math::getScalarSignum(reference, circlepoint-pivotpoint);
			
				if (loopcounter != 0 && i != previ) {
					
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

					if (util::Math::getScalarSignum(crossproduct, intersection - pivotpoint) >= 0) {
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
				loopcounter++;
				subtract = 0;
			}
			
			tracks[j].push_back(finalintersections[j]);
			//addtoManual(finalintersections[j],finalintersections[j] -n*1,Ogre::ColourValue(0,1,1));
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

		addtoManual(runners[0],runners[1],(runners[0]-sourcepoints[0]).normalize(), (runners[1]-sourcepoints[1]).normalize(), Ogre::ColourValue(0,0,1));

		double ratio[2];
		int faster = 0;
		int slower = 0;
		int cnt = 0;
		double l = 0;
		int cnts[2] = { 2 , 2};


		while (runneddistance[0] + runneddistance[1] < (perimeters[0] + perimeters[1])*0.95f ) { // && it[0] !=tracks[0].end() && it[1] !=tracks[1].end()) {
			
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
			
			addtoManual(runners[0],runners[1],(runners[0]-sourcepoints[0]).normalize(), (runners[1]-sourcepoints[1]).normalize(), Ogre::ColourValue(0.7,0.7,0,0.5));
			
			if (finalintersections[0] == nexpoints[0] && finalintersections[1] == nexpoints[1]) {
				runneddistance[0] += (nexpoints[0] - runners[0]).length();
				runneddistance[1] += (nexpoints[1] - runners[1]).length();
				addtoManual(nexpoints[0],nexpoints[1],(nexpoints[0]-sourcepoints[0]).normalize(), (nexpoints[1]-sourcepoints[1]).normalize(),Ogre::ColourValue(0,0,1,0.5));
				break;
			}

		}
	}


	
	ManualObject* createHull(Passage p, SceneManager * mScrMgr) {
		
		createManualObject(mScrMgr);

		int available = p.points.size()-1;

		for (std::vector<SourcePoint>::iterator it = p.points.begin(); available > 0; )
		{
			double perimeters[2];
			Vector finalintersections[2];
			std::vector<Vector> tracks[2];
			Vector pivotpoints[2];
			SourcePoint p1 = *it;
			++it;
			available --;
			SourcePoint p2 = *it;
		
			getTracks(p1,p2, tracks, perimeters, finalintersections,pivotpoints);
			
			jointTracks(tracks, finalintersections, pivotpoints, perimeters);
			
		}

		manual->end();
		return manual;
	}
private:
	void createManualObject(SceneManager *mSceneMgr) {

		manual = mSceneMgr->createManualObject("proba");
		manual->setDynamic(true);
		manual->begin("Test2/ColourTest", Ogre::RenderOperation::OT_TRIANGLE_STRIP);
	}

	void addtoManual(Vector p1, Vector p2, Vector n1, Vector n2,Ogre::ColourValue color) {

		manual->position(p1.x,p1.y,p1.z);
		manual->normal(n1.x, n1.y, n1.z);
		manual->colour(color);
		manual->position(p2.x,p2.y,p2.z);
		manual->normal(n2.x,n2.y,n2.z);
		manual->colour(color);
	}

	void debug(char * s) {
		OutputDebugString(s);
		
	}

};