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