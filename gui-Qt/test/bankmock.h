#ifndef BANKMOCK_H
#define BANKMOCK_H

#include <string>
#include <gmock/gmock.h>

#include "bank.h"

namespace ClubFrontendTest
{

class BankMock : public ClubFrontend::Bank
{
public:
	BankMock();

	MOCK_METHOD1(setAccount, void(const int& anAccount));
	MOCK_CONST_METHOD0(getAccount, int());

	MOCK_METHOD1(setName, void(const std::string& aName));
	MOCK_CONST_METHOD0(getName, std::string());
	
	MOCK_METHOD1(setCode, void(const int& aCode));
	MOCK_CONST_METHOD0(getCode, int());
};

}

#endif // BANKMOCK_H
