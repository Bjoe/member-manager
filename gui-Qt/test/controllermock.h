#ifndef CONTROLLERMOCK_H
#define CONTROLLERMOCK_H

#include "../src/controller.h"
#include "membermock.h"
#include "bankmock.h"
#include "contributionmock.h"

namespace ClubFrontendTest
{

class ControllerMock : public ClubFrontend::Controller
{
public:
	ControllerMock(MemberMock* aMember,
	               BankMock* aBank,
	               ContributionMock* aContribution);

	void saveMember(const ClubFrontend::Member* aMember,
	                const ClubFrontend::Bank* aBank,
	                const ClubFrontend::Contribution* aContribution);
	ClubFrontend::Member* getMember() const;
	ClubFrontend::Bank* getBank() const;
	ClubFrontend::Contribution* getContribution() const;

	const MemberMock* getMemberMock() const;
	const BankMock* getBankMock() const;
	const ContributionMock* getContributionMock() const;

private:
	MemberMock* memberMock;
	BankMock* bankMock;
	ContributionMock* contributionMock;
	const ClubFrontend::Member* member;
	const ClubFrontend::Bank* bank;
	const ClubFrontend::Contribution* contribution;
};

}

#endif // CONTROLLERMOCK_H
