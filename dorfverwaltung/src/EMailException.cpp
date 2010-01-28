#include "EMailException.hpp"

namespace ClubBackend
{

EMailException::EMailException() throw()
{
}

EMailException::EMailException(const std::string& aMessage) : message(aMessage)
{
	//ctor
}

EMailException::~EMailException() throw()
{
}

std::string EMailException::getMessage() const
{
	return message;
}

const char* EMailException::what() const throw()
{
	return message.c_str();
}
}
