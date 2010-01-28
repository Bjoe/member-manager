#ifndef MEMBERMOCK_H
#define MEMBERMOCK_H

#include <string>
#include "../src/member.h"

namespace ClubFrontendTest
{

class MemberMock : public ClubFrontend::Member
{
public:
	MemberMock();

	virtual void setId(const int& anId) {
		memberId = anId;
	}

	virtual int getId() const {
		return memberId;
	}

	virtual void setName(const std::string& aName) {
		name = aName;
	}

	virtual std::string getName() const {
		return name;
	}

	virtual void setFirstname(const std::string& aName) {
		firstname = aName;
	}

	virtual std::string getFirstname() const {
		return firstname;
	}

	virtual void setNickname(const std::string& aNickname) {
		nickname = aNickname;
	}

	virtual std::string getNickname() const {
		return nickname;
	}

	virtual void setEmail(const std::string& anEmail) {
		email = anEmail;
	}

	virtual std::string getEmail() const {
		return email;
	}

	virtual void setCity(const std::string& aCity) {
		city = aCity;
	}

	virtual std::string getCity() const {
		return city;
	}

	virtual void setZipCode(const int& aZipcode) {
		zip = aZipcode;
	}

	virtual int getZipCode() const {
		return zip;
	}

	virtual void setStreet(const std::string& aStreet) {
		street = aStreet;
	}

	virtual std::string getStreet() const {
		return street;
	}

	virtual void setEntryDate(const std::string& aDate) {
		date = aDate;
	}

	virtual std::string getEntryDate() const {
		return date;
	}

	virtual void setInfo(const std::string& anInfo) {
		info = anInfo;
	}

	virtual std::string getInfo() const {
		return info;
	}

private:
	int memberId;
	std::string name;
	std::string firstname;
	std::string nickname;
	std::string email;
	std::string city;
	int zip;
	std::string street;
	std::string date;
	std::string info;
};

}

#endif // MEMBERMOCK_H
