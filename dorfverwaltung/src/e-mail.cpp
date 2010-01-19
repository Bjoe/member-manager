#include "e-mail.hpp"

EMail::EMail(const std::string anEmail) : address(anEmail)
{
	const boost::regex expr(".*");
	if(! boost::regex_match(address, expr)) {
		throw std::exception();
	}
}

EMail::~EMail()
{
}
