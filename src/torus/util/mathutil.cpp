#include "mathutil.h"


int util::Math::getScalarSignum(Vector v1, Vector v2) {
	double crossresult = v1.dot(v2);
		if (crossresult > 0 )  {
			return 1;
		} else if (crossresult < 0) {
			return -1;
		} else {
			return 0;
		}
}
	

Vector util::Math::getIntersection(Vector r0,Vector p2, Vector P,Vector n) {

	Vector result;
	n = n.normalize();
	Vector v = (p2 - r0).normalize();
	double t = 0;
	t = ((P-r0).dot(n))/(v.dot(n));
	result = r0 + v * t;
	return result;
}

double util::Math::getAngle(Vector v1,Vector v2) {

	return acos(v1.normalize().dot(v2.normalize()));
}

simplex::Plane util::Math::getBestFittingPlane(SourcePoint &p) {
	int size = p.points.size();
	float *points = new float[size*3];
	int cnt = 0;
	for (std::vector<EndPoint>::iterator it = p.points.begin(); it != p.points.end();++it) {
		points[cnt++] = it->x;
		points[cnt++] = it->y;
		points[cnt++] = it->z;
	}

	float plane[4];
	
	getBestFitPlane(3,points,sizeof(float)*3,0,0,plane);
	//printf("Plane: %f %f %f %f\r\n", plane[0], plane[1], plane[2] );
	return simplex::Plane(plane[0], plane[1], plane[2], plane[3]);
}