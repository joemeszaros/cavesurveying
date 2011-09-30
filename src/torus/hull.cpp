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

	ManualObject* createHull(Passage p, SceneManager * mScrMgr) {
		
		createManualObject(mScrMgr);
		

		Point from, to;
		Vector n, reference, randomvector;
		
		SourcePoint bfrom = p.points.front();
		from = Point(bfrom.x, bfrom.y,bfrom.z);
		SourcePoint bto = p.points.back();
		to = Point(bto.x,bto.y,bto.z);

		n = (to-from).normalize();
		
		addtoManual(from, from + n, Ogre::ColourValue(0.6,0.6,1));
		//addtoManual(Point(0,0,0),Point(-10,3,3),Ogre::ColourValue(1,1,0));

		double minvalue = 1.0;
		if (abs(n.x) < minvalue) { minvalue = n.x; randomvector = Vector(1,0,0); }
		if (abs(n.y) < minvalue) { minvalue = n.y; randomvector = Vector(0,1,0); }
		if (abs(n.z) < minvalue) { minvalue = n.z; randomvector = Vector(0,0,1); }

		reference = n.cross(randomvector);
		reference = reference.normalize();
		addtoManual(from+n, from+n + reference ,Ogre::ColourValue(0,1,1));

		double idistance = -1.0, crossresult, dist;
		Point finalintersection, intersection;

		Point runners[2];
		Point nexpoints[2];
		
		SourcePoint bsourcepoints[2];
		Point sourcepoints[2];
		double perimeters[2];
		double runneddistance[2];
		std::vector<Point> tracks;
		std::vector<Point> visitedstations;

		bsourcepoints[0] = bfrom;
		bsourcepoints[1] = bto;
		sourcepoints[0] = from;
		sourcepoints[1] = to;
		//track[0] =  std::vector<Point>

		int previ = 0,i = 0, loopcounter = 0;
		Point prevcirclepoint ;
		
		Point crossproduct = n.cross(reference).normalize();
		for(int j=0; j<2;j++) {
			loopcounter = 0;
			idistance = -1.0;
			for(std::vector<BasePoint>::iterator it = bsourcepoints[j].points.begin(); it != bsourcepoints[j].points.end();++it) {
				Point circlepoint = Point(it->x, it->y, it->z);

				i = getScalarSignum(reference, circlepoint-sourcepoints[j]);
			
				if (loopcounter != 0 && i != previ) {
					debug("intersection");
					if (i * previ == 0 && (i+previ) == 0) { //2 on the plane
						intersection = ((prevcirclepoint-sourcepoints[j]).length() > (circlepoint-sourcepoints[j]).length()) ? prevcirclepoint : circlepoint;
					} else if (i * previ == 0 && (i+previ) != 0) { // 1 on the plane
						intersection = (i == 0 ? circlepoint : prevcirclepoint);
					} else if (i * previ == -1) { // 0 on the plane
						intersection = getIntersection(prevcirclepoint, circlepoint, sourcepoints[j], reference);
					}

					if (getScalarSignum(crossproduct, intersection - sourcepoints[j]) >= 0) {
							dist = (intersection - sourcepoints[j]).length();
							if (dist > idistance){
								finalintersection = intersection;
								idistance = dist;
							}
						}
				}
				
				previ = i;
				prevcirclepoint = circlepoint;
				loopcounter++;
			}

			addtoManual(finalintersection,finalintersection -n*1,Ogre::ColourValue(0,1,1));
		}
		
		manual->end();
		return manual;
	}
private:
	void createManualObject(SceneManager *mSceneMgr) {

		manual = mSceneMgr->createManualObject("proba");
		manual->setDynamic(true);
		manual->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_LIST);
	}

	void addtoManual(Point p1, Point p2,Ogre::ColourValue color) {

		manual->position(p1.x,p1.y,p1.z);
		manual->colour(color);
		manual->position(p2.x,p2.y,p2.z);
		manual->colour(color);
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