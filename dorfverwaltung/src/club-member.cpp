//           mitglied.cpp
//  Fri Apr  3 07:35:05 2009
//  Copyright  2009  joerg
//  <joerg@<host>>

#include "club-member.hpp"

ClubMember::ClubMember(const DorfManagement& aDb) : member(aDb) {
}

void ClubMember::setEntryDate(boost::gregorian::date anEntryDate) {
	litesql::Date sqlDate(anEntryDate.day(),anEntryDate.month(),anEntryDate.year());
	member.dateOfEntry = sqlDate;
}

boost::gregorian::date ClubMember::getEntryDate() {
	litesql::Date sqlDate = member.dateOfEntry;
	return boost::gregorian::date(sqlDate.year(),sqlDate.month(),sqlDate.day());
}

void ClubMember::setLeavingDate(boost::gregorian::date anLeavingDate) {
	litesql::Date sqlDate(anLeavingDate.day(),anLeavingDate.month(),anLeavingDate.year());
	member.dateOfEntry = sqlDate;
}

boost::gregorian::date ClubMember::getLeavingDate() {
	litesql::Date sqlDate = member.dateOfEntry;
	return boost::gregorian::date(sqlDate.year(),sqlDate.month(),sqlDate.day());
}

void ClubMember::setEmail(string anEmailAdr) {
	// TODO auf Email Adr. Pruefen!
	member.email = anEmailAdr;
}

string ClubMember::getEmail() {
	return member.email;
}
