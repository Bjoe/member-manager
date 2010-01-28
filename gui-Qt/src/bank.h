#ifndef BANK_H
#define BANK_H

#include <string>

namespace ClubFrontend
{

class Bank
{
public:
	virtual ~Bank() {}
	virtual void setAccount(const int&) = 0;
	virtual int getAccount() const = 0;
	virtual void setName(const std::string&) = 0;
	virtual std::string getName() const = 0;
	virtual void setCode(const int&) = 0;
	virtual int getCode() const = 0;
};

}

#endif // BANK_H
