//           mitglied.cpp
//  Fri Apr  3 07:35:05 2009
//  Copyright  2009  joerg
//  <joerg@<host>>

#include "Member.hpp"

namespace ClubBackend
{

Member::Member(const MemberManagement::DorfManagement& aDatabase) : member(aDatabase)
{
}

Member::Member(const litesql::Database& aDatabase, const litesql::Record& aRecord) : member(aDatabase,aRecord)
{
}

void Member::setEntryDate(const boost::gregorian::date& anEntryDate)
{
	litesql::Date sqlDate(anEntryDate.day(),anEntryDate.month(),anEntryDate.year());
	member.dateOfEntry = sqlDate;
}

boost::gregorian::date Member::getEntryDate() const
{
	litesql::Date sqlDate = member.dateOfEntry;
	return boost::gregorian::date(sqlDate.year(),sqlDate.month(),sqlDate.day());
}

void Member::setLeavingDate(const boost::gregorian::date& anLeavingDate)
{
	litesql::Date sqlDate(anLeavingDate.day(),anLeavingDate.month(),anLeavingDate.year());
	member.dateOfEntry = sqlDate;
}

boost::gregorian::date Member::getLeavingDate() const
{
	litesql::Date sqlDate = member.dateOfEntry;
	return boost::gregorian::date(sqlDate.year(),sqlDate.month(),sqlDate.day());
}

void Member::setEmail(const EMail::EMail& anEmailAdr)
{
	member.email = anEmailAdr.getAddress();
}

EMail::EMail Member::getEmail() const
{
	return EMail::EMail(member.email);
}
}
