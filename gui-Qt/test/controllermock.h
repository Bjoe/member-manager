#ifndef CONTROLLERMOCK_H
#define CONTROLLERMOCK_H

#include <gmock/gmock.h>

#include "controller.h"
#include "member.h"
#include "bank.h"
#include "contribution.h"

namespace ClubFrontendTest
{

class ControllerMock : public ClubFrontend::Controller
{
public:
	ControllerMock();
		
	MOCK_METHOD3(saveMember, void(const ClubFrontend::Member* aMember,
	                const ClubFrontend::Bank* aBank,
	                const ClubFrontend::Contribution* aContribution));
		
	MOCK_CONST_METHOD0(getMember, ClubFrontend::Member*());
	MOCK_CONST_METHOD0(getBank, ClubFrontend::Bank*());
	MOCK_CONST_METHOD0(getContribution, ClubFrontend::Contribution*());

};

}

#endif // CONTROLLERMOCK_H
