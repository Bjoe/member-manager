#ifndef MEMBERMOCK_H
#define MEMBERMOCK_H

#include <string>
#include <gmock/gmock.h>
#include "../src/member.h"

namespace ClubFrontendTest
{

class MemberMock : public ClubFrontend::Member
{
public:
	MemberMock();

	MOCK_METHOD1(setId, void(const int& anId));
	MOCK_CONST_METHOD0(getId, int());

	MOCK_METHOD1(setName, void(const std::string& aName));
	MOCK_CONST_METHOD0(getName, std::string());

	MOCK_METHOD1(setFirstname, void(const std::string& aName));
	MOCK_CONST_METHOD0(getFirstname, std::string());

	MOCK_METHOD1(setNickname, void(const std::string& aNickname));
	MOCK_CONST_METHOD0(getNickname, std::string());

	MOCK_METHOD1(setEmail, void(const std::string& anEmail));
	MOCK_CONST_METHOD0(getEmail, std::string());

	MOCK_METHOD1(setCity, void(const std::string& aCity));
	MOCK_CONST_METHOD0(getCity, std::string());

	MOCK_METHOD1(setZipCode, void(const int& aZipcode));
	MOCK_CONST_METHOD0(getZipCode, int());

	MOCK_METHOD1(setStreet, void(const std::string& aStreet));
	MOCK_CONST_METHOD0(getStreet, std::string());

	MOCK_METHOD1(setEntryDate, void(const std::string& aDate));
	MOCK_CONST_METHOD0(getEntryDate, std::string());

	MOCK_METHOD1(setInfo, void(const std::string& anInfo));
	MOCK_CONST_METHOD0(getInfo, std::string());
};

}

#endif // MEMBERMOCK_H
