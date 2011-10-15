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

class StringIdCmp {
	public:
		bool operator() (const std::string& s1, const std::string& s2) const {
			return (double)atof(s1.c_str()) < (double)atof(s2.c_str());
		}
	};
}






#endif