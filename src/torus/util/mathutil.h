#include "point.h"

#ifndef MATHUTIL_H
#define MATHUTIL_H

namespace util
{
	class Math
	{
	public:
		static int getScalarSignum(Vector v1, Vector v2);
		static Vector getIntersection(Vector r0,Vector p2, Vector P,Vector n);
	};
}
#endif