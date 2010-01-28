#ifndef CONTROLLERMOCK_H
#define CONTROLLERMOCK_H

#include "../src/controller.h"
#include "membermock.h"
#include "bankmock.h"
#include "contributionmock.h"
#include "resourcesmock.h"

namespace ClubFrontendTest
{

class ControllerMock : public ClubFrontend::Controller
{
public:
	ControllerMock(MemberMock* aMember,
	               BankMock* aBank,
	               ContributionMock* aContribution,
	               ResourcesMock* aResources);

	void saveMember(const ClubFrontend::Member* aMember,
	                const ClubFrontend::Bank* aBank,
	                const ClubFrontend::Contribution* aContribution,
	                const ClubFrontend::Resources* aResources);
	ClubFrontend::Member* getMember() const;
	ClubFrontend::Bank* getBank() const;
	ClubFrontend::Contribution* getContribution() const;
	ClubFrontend::Resources* getResources() const;

	const MemberMock* getMemberMock() const;
	const BankMock* getBankMock() const;
	const ContributionMock* getContributionMock() const;
	const ResourcesMock* getResourcesMock() const;

private:
	MemberMock* memberMock;
	BankMock* bankMock;
	ContributionMock* contributionMock;
	ResourcesMock* resourcesMock;
	const ClubFrontend::Member* member;
	const ClubFrontend::Bank* bank;
	const ClubFrontend::Contribution* contribution;
	const ClubFrontend::Resources* resources;
};

}

#endif // CONTROLLERMOCK_H
