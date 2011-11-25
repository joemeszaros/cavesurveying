#include "point.h"
#include "graphics.h"

#ifndef COMPLEX_H
#define COMPLEX_H

namespace complex {
	class Ring {
	public: 
		std::vector<std::pair<graphics::Vertex, graphics::Vertex>> segments;
	};

	class Worm {
	public:
		std::vector<Ring> rings;
	};
}
#endif