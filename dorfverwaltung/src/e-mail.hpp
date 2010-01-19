#ifndef __email__
#define __email__

#include <string>
#include <exception>
#include <boost/regex.hpp>

class EMail {
private:
	std::string address;
	
public:
	EMail(const std::string anEmail);
	~EMail();
	
	std::string getAddress() {
		return address;
	}

};
#endif // __email__
