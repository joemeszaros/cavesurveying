#include <string>
#include <sstream>

#ifndef UTIL_H
#define UTIL_H

namespace util {

class String
{
	public:
		static std::string ToString(long value) {
			std::stringstream ss;
			 ss << value;
			return ss.str();
		}

		static std::string ToString(int value) {
			std::stringstream st;
			st << value;
			return st.str();
		}
		
	};

}

#endif