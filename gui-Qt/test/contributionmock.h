#ifndef CONTRIBUTIONMOCK_H
#define CONTRIBUTIONMOCK_H

#include <string>
#include <gmock/gmock.h>

#include "contribution.h"

namespace ClubFrontendTest
{

class ContributionMock : public ClubFrontend::Contribution
{
public:
	ContributionMock();

	MOCK_METHOD1(setFee, void(const int& aFee));
	MOCK_CONST_METHOD0(getFee, int());
	
	MOCK_METHOD1(setDonation, void(const int& aDonation));
	MOCK_CONST_METHOD0(getDonation, int());
	
	MOCK_METHOD1(setInfo, void(const std::string& anInfo));
	MOCK_CONST_METHOD0(getInfo, std::string());
	
	MOCK_METHOD1(setValidFrom, void(const std::string& aDate));
	MOCK_CONST_METHOD0(getValidFrom, std::string());
};

}

#endif // CONTRIBUTIONMOCK_H
