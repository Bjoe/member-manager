#include "controllermock.h"

namespace ClubFrontendTest
{

ControllerMock::ControllerMock(MemberMock* aMember,
                               BankMock* aBank,
                               ContributionMock* aContribution)
		: memberMock(aMember), bankMock(aBank), contributionMock(aContribution)
{
}

void ControllerMock::saveMember(const ClubFrontend::Member* aMember,
                                const ClubFrontend::Bank* aBank,
                                const ClubFrontend::Contribution* aContribution)
{
	member = aMember;
	bank = aBank;
	contribution = aContribution;
}

ClubFrontend::Member* ControllerMock::getMember() const
{
	return memberMock;
}

const MemberMock* ControllerMock::getMemberMock() const
{
	const MemberMock* obj = static_cast<const MemberMock*>(member);
	return obj;
}

ClubFrontend::Bank* ControllerMock::getBank() const
{
	return bankMock;
}

const BankMock* ControllerMock::getBankMock() const
{
	const BankMock* obj = static_cast<const BankMock*>(bank);
	return obj;
}

ClubFrontend::Contribution* ControllerMock::getContribution() const
{
	return contributionMock;
}

const ContributionMock* ControllerMock::getContributionMock() const
{
	const ContributionMock* obj = static_cast<const ContributionMock*>(contribution);
	return obj;
}

}
