#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "member.h"
#include "bank.h"
#include "contribution.h"

namespace ClubFrontend
{

class Controller
{
public:
	virtual ~Controller() {}
	virtual Member* getMember() const = 0;
	virtual Bank* getBank() const = 0;
	virtual Contribution* getContribution() const = 0;
	virtual void saveMember(const Member* aMember,
	                        const Bank* aBank,
	                        const Contribution* aContribution) = 0;
};

}

#endif // CONTROLLER_H
