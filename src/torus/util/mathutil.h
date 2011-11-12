#include <utility>
#include "../point.h"
#include "../passage.h"
#include "../math/bestfitplane.h"

#ifndef MATHUTIL_H
#define MATHUTIL_H

using namespace std;
using namespace simplex;

namespace util
{
	class Math
	{
	public:
		static int getDotSignum(Vector v1, Vector v2);
		static simplex::Vector getIntersection(Vector r0,Vector p2, Vector P,Vector n);
		static double getAngle(Vector v1,Vector v2);
		static double getAngle(Vector v1,Vector v2, Vector normal);
		static simplex::Plane getBestFittingPlane(SourcePoint &p);
		static SourcePoint orderEndPoints(SourcePoint &orig,simplex::Plane &plane);
		static float getPlaneDistance(Vector &planepoint, Vector &normal, Vector &point);
		static int getPlaneSignum(Vector &planepoint, Vector &normal, Vector &point);
	};
}
#endif