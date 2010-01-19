/***************************************************************************
 *            mitglied.hpp
 *
 *  Fri Apr  3 07:34:14 2009
 *  Copyright  2009  joerg
 *  <joerg@<host>>
 ****************************************************************************/

#ifndef _CLUB_MEMBER_HPP_
#define _CLUB_MEMBER_HPP_

#include <iostream>
#include <litesql.hpp>
#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>
#include "dorfmanagement.hpp"

using namespace std;

using namespace MemberManagement;

class ClubMember {

private:
	Member member;

public:
	ClubMember(const DorfManagement&);

	void setEntryDate(boost::gregorian::date);
	boost::gregorian::date getEntryDate();

	void setLeavingDate(boost::gregorian::date);
	boost::gregorian::date getLeavingDate();

	void setEmail(string);
	string getEmail();

	void setId(int anId) {
		member.memberId = anId;
	}

	int getId() {
		return member.memberId;
	}
	
	void setDeleted(bool aDeleted) {
		member.deleted = aDeleted;
	}
	
	bool getDeleted() {
		return member.deleted;
	}

	void setCashCollection(bool aCashCollection) {
		member.cashCollection = aCashCollection;
	}
	
	bool getCashCollection() {
		return member.cashCollection;
	}

	void setName(string aName) {
		member.surename = aName;
	}

	string getName() {
		return member.surename;
	}

	void setFirstname(string aName) {
		member.firstName = aName;
	}

	string getFirstname() {
		return member.firstName;
	}

	void setNickname(string aNickname) {
		member.nickname = aNickname;
	}

	string getNickname() {
		return member.nickname;
	}

	void setStreet(string aStreet) {
		member.street = aStreet;
	}
	
	string getStreet() {
		return member.street;
	}
	
	void setZipCode(int aZipCode) {
		member.zipCode = aZipCode;
	}
	
	int getZipCode() {
		return member.zipCode;
	}
	
	void setCity(string aCity) {
		member.city = aCity;
	}
	
	string getCity() {
		return member.city;
	}
	
	void setInfo(string anInfo) {
		member.info = anInfo;
	}
	
	string getInfo() {
		return member.info;
	}
};

#endif // _MCLUB_MEMBER_HPP_
