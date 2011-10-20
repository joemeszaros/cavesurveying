#include "../point.h"
#include "../passage.h"
#include "../math/bestfitplane.h"

#ifndef MATHUTIL_H
#define MATHUTIL_H

namespace util
{
	class Math
	{
	public:
		static int getScalarSignum(Vector v1, Vector v2);
		static simplex::Vector getIntersection(Vector r0,Vector p2, Vector P,Vector n);
		static double getAngle(Vector v1,Vector v2);
		static simplex::Plane getBestFittingPlane(SourcePoint &p);
	};
}
#endif