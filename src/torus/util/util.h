#include <string>
#include <sstream>

typedef unsigned long DWORD;

namespace myutil {

class StringUtil
{
	public:
		static std::string ToString(DWORD value) {
			std::stringstream ss;
			 ss << value;
			return ss.str();
		}
		
	};

}



