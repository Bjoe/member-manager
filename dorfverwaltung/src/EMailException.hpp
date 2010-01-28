#ifndef EMAILEXCEPTION_H
#define EMAILEXCEPTION_H

#include <exception>
#include <string>

namespace ClubBackend
{

class EMailException : public std::exception
{
public:
	EMailException() throw();
	virtual ~EMailException() throw();

	EMailException(const std::string& aMessage);
	std::string getMessage() const;
	virtual const char* what() const throw();
protected:
private:
	std::string message;
};
}

#endif // EMAILEXCEPTION_H
