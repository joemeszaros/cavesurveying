#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "point.h"

using namespace simplex;

namespace graphics  {
	struct Colour {
		double r;
		double g;
		double b;
		Colour(double r, double g, double b) {
			this->r = r;
			this->g = g;
			this->b = b;
		}
	};

	class Vertex {
		public :
			std::string name;
			simplex::Vector position;
			simplex::Vector normal;
			double* uv;

			Vertex(const char * name, Vector &pos, Vector &n, double uv[]) {
				this->name.assign(name);
				this->position = pos;
				this->normal = n;
				this->uv = uv;
				
			}
	};

}
#endif