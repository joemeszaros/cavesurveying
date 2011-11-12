#include "mathutil.h"


int util::Math::getDotSignum(Vector v1, Vector v2) {
		double crossresult = v1.dot(v2);
		if (crossresult > 0 )  {
			return 1;
		} else if (crossresult < 0) {
			return -1;
		} else {
			return 0;
		}
}

float util::Math::getPlaneDistance(Vector &planepoint, Vector &normal, Vector &point) {
	return normal.dot(point-planepoint);
}

int util::Math::getPlaneSignum(Vector &planepoint, Vector &normal, Vector &point) {
	float dist = getPlaneDistance(planepoint, normal, point);
	if (dist > 0) {
		return 1;
	} else if (dist < 0) {
		return -1;
	} else {
		return 0;
	}
}
	
//
// r0: the first point of the line
// p2: the second point of the line
// P : point of the plane
// n : normal vector of the plane
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
	
	getBestFitPlane(size,points,sizeof(float)*3,0,0,plane);
	//printf("Plane: %f %f %f %f\r\n", plane[0], plane[1], plane[2] );
	return simplex::Plane(plane[0], plane[1], plane[2], plane[3]);
}



bool MyDataSortPredicate(const pair<int, double>& d1, const pair<int, double>& d2)
{
	return d1.second < d2.second;
}

SourcePoint util::Math::orderEndPoints(SourcePoint &orig,simplex::Plane &plane) {
	SourcePoint ordered(orig.x, orig.y, orig.z);
	std::vector<pair<int, double>> v;

	Vector first;
	Vector sourceprojected = plane.getProjection(Vector(orig.x,orig.y,orig.y));
	int cnt = 0;

	for (std::vector<EndPoint>::iterator it = orig.points.begin(); it != orig.points.end();++it) {
		Vector projected =  plane.getProjection(*it);
		
		if (0 == cnt) {
			first = (projected-sourceprojected);
			ordered.points.push_back(*it);
		}
		pair<int, double> current(cnt, getAngle((first-sourceprojected), (projected-sourceprojected), plane.normal));
		v.push_back(current);
		cnt++;
	}

	std::sort(v.begin(), v.end(),MyDataSortPredicate);

	for (std::vector<pair<int, double>>::iterator it = v.begin(); it != v.end(); ++it) {
		if (it->first != 0) {
			ordered.points.push_back(orig.points.at(it->first));
		}
	}
	
	return ordered;

}

double util::Math::getAngle(Vector v1,Vector v2, Vector normal)    {

	normal.normalize();
	double angle =  acos(v1.normalize().dot(v2.normalize()));
	Vector cross = v1.cross(v2).normalize();

	if ((cross + normal).length() > 0.5) {
		return angle;
	} else {
		return -angle + 360.0;
	}
}