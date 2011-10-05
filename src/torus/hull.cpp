#include<windows.h>
#include "point.h"
#include "passage.h"
#include "OgreManualObject.h"
#include "OgreSceneManager.h"
typedef Point Vector;

using namespace Ogre;

class Hull {
public:
	ManualObject* manual;

	void getTracks(SourcePoint sourcefrom, SourcePoint sourceto, std::vector<Point> tracks[],double perimeters[], Point finalintersections[]) {

		Point from, to;
		Vector n, reference, randomvector;
		
		SourcePoint bfrom = sourcefrom;
		from = bfrom.toPoint();
		SourcePoint bto = sourceto;//.back();
		to = sourceto.toPoint();

		SourcePoint bsourcepoints[2] = {sourcefrom, sourceto};
		Point sourcepoints[2] = {from,to};

		n = (to-from).normalize();
		
		//addtoManual(from, from + n, Ogre::ColourValue(0.6,0.6,1));
		//addtoManual(Point(0,0,0),Point(-10,3,3),Ogre::ColourValue(1,1,0));

		//create random vector
		double minvalue = 1.0;
		if (abs(n.x) < minvalue) { minvalue = n.x; randomvector = Vector(1,0,0); }
		if (abs(n.y) < minvalue) { minvalue = n.y; randomvector = Vector(0,1,0); }
		if (abs(n.z) < minvalue) { minvalue = n.z; randomvector = Vector(0,0,1); }

		reference = n.cross(randomvector);
		reference = reference.normalize();
		//addtoManual(from+n, from+n + reference ,Ogre::ColourValue(0,1,1));

		double idistance = -1.0, crossresult, dist;
		Point intersection;


//		double perimeters[2];

		double finalloopcounters[2];
		double subtract = 0,t = 0;
		bool predicate = false;

		//std::vector<Point> tracks[2];
		std::vector<Point> visitedstations[2];


		for	(int index = 0; index < 2; index++) {
			perimeters[index] = 0;
			//-runneddistance[index] = 0;
		}
		

		int previ = 0,i = 0, loopcounter = 0;
		Point prevcirclepoint,circlepoint ;
		
		Point crossproduct = n.cross(reference).normalize();

		for(int j=0; j<2;j++) {
			loopcounter = 0;
			idistance = -1.0;
			for(std::vector<BasePoint>::iterator it = bsourcepoints[j].points.begin(); it != bsourcepoints[j].points.end();++it) {
				circlepoint = it->toPoint();

				i = getScalarSignum(reference, circlepoint-sourcepoints[j]);
			
				if (loopcounter != 0 && i != previ) {
					
					if (i * previ == 0 && (i+previ) == 0) { //2 on the plane
						predicate = (prevcirclepoint-sourcepoints[j]).length() > (circlepoint-sourcepoints[j]).length();
						intersection =  predicate ? prevcirclepoint : circlepoint;
						subtract = (predicate ? 1.0 : 0);
					} else if (i * previ == 0 && (i+previ) != 0) { // 1 on the plane
						intersection = (i == 0 ? circlepoint : prevcirclepoint);
						subtract = (i == 0 ? 0 : 1 );
					} else if (i * previ == -1) { // 0 on the plane
						intersection = getIntersection(prevcirclepoint, circlepoint, sourcepoints[j], reference);
						subtract = 0.5;
					}

					if (getScalarSignum(crossproduct, intersection - sourcepoints[j]) >= 0) {
							dist = (intersection - sourcepoints[j]).length();
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

		Point first;
		for(int j=0; j<2;j++) {
			loopcounter = 0;
			
			for(std::vector<BasePoint>::iterator it = bsourcepoints[j].points.begin(); it != bsourcepoints[j].points.end();++it) {
				circlepoint = it->toPoint();

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

			for(std::vector<Point>::iterator it = visitedstations[j].begin(); it != visitedstations[j].end();++it) {
				tracks[j].push_back(*it);
			}

			tracks[j].push_back(finalintersections[j]);

		}



	}


	void jointTracks(std::vector<Point> tracks[], Point finalintersections[], double perimeters[]) {
		
		Point runners[2];
		Point nexpoints[2];
		double runneddistance[2];

		for	(int index = 0; index < 2; index++) {
			runneddistance[index] = 0;
		}
		

		std::vector<Point>::iterator it[2];
		for(int j=0; j<2;j++) {
			it[j] = tracks[j].begin();
			
			runners[j] = *it[j];
			++(it[j]);
			nexpoints[j] = *it[j];
		}

		addtoManual(runners[0],runners[1],Ogre::ColourValue(0,0,1));

		double ratio[2];
		int faster = 0;
		int slower = 0;
		int cnt = 0;
		double l = 0;

		while (runneddistance[0] + runneddistance[1] != perimeters[0] + perimeters[1]) { // && it[0] !=tracks[0].end() && it[1] !=tracks[1].end()) {
			
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
				if (it[slower] != tracks[slower].end()) {
					++(it[slower]);
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
			
			addtoManual(runners[0],runners[1],Ogre::ColourValue(0.7,0.7,0,0.5));
			
			if (finalintersections[0] == nexpoints[0] && finalintersections[1] == nexpoints[1]) {
				runneddistance[0] += (nexpoints[0] - runners[0]).length();
				runneddistance[1] += (nexpoints[1] - runners[1]).length();
				addtoManual(nexpoints[0],nexpoints[1],Ogre::ColourValue(0,0,1,0.5));
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
			Point finalintersections[2];
			std::vector<Point> tracks[2];
			SourcePoint p1 = *it;
			++it;
			available --;
			SourcePoint p2 = *it;
			
			getTracks(p1,p2, tracks, perimeters, finalintersections);
			
			jointTracks(tracks, finalintersections, perimeters);
			
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

	void addtoManual(Point p1, Point p2,Ogre::ColourValue color) {

		manual->position(p1.x,p1.y,p1.z);
		//manual->colour(color);
		manual->position(p2.x,p2.y,p2.z);
		//manual->colour(color);
	}

	void debug(char * s) {
		OutputDebugString(s);
		
	}

	int getScalarSignum(Vector v1, Vector v2) {
		double crossresult = v1.dot(v2);
			if (crossresult > 0 )  {
				return 1;
			} else if (crossresult < 0) {
				return -1;
			} else {
				return 0;
			}
	}
	
	Point getIntersection(Point r0,Point p2, Point P,Vector n) {
		Point result;
		n = n.normalize();
		Vector v = (p2 - r0).normalize();
		double t = 0;
		t = ((P-r0).dot(n))/(v.dot(n));
		result = r0 + v * t;
		return result;
	}

};