#include <UnitTest++.h>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <litesql.hpp>

#include "../src/dorfmanagement.hpp"
#include "../src/club-member.hpp"

MemberManagement::DorfManagement createDb() {
	MemberManagement::DorfManagement memberdb("sqlite3", "database=test.db");
	memberdb.verbose = true;
	//memberdb.create(); bei existierenden Schema, Exception!
	return memberdb;
}

TEST(Name) {
	MemberManagement::DorfManagement memberdb = createDb();
	ClubMember member(memberdb);

	member.setName("Kirk");
	CHECK_EQUAL("Kirk",member.getName());
}

TEST(FirstName) {
	MemberManagement::DorfManagement memberdb = createDb();
	ClubMember member(memberdb);

	member.setFirstname("james");
	CHECK_EQUAL("james",member.getFirstname());
}

TEST(NickName) {
	MemberManagement::DorfManagement memberdb = createDb();
	ClubMember member(memberdb);

	member.setNickname("jamesT");
	CHECK_EQUAL("jamesT",member.getNickname());
}

TEST(Email) {
	MemberManagement::DorfManagement memberdb = createDb();
	ClubMember member(memberdb);

	member.setEmail("joerg@localhost.de");
	CHECK_EQUAL("joerg@localhost.de", member.getEmail());
}

TEST(Street) {
	MemberManagement::DorfManagement memberdb = createDb();
	ClubMember member(memberdb);

	member.setStreet("Bunsenhausen");
	CHECK_EQUAL("Bunsenhausen", member.getStreet());
}

TEST(ZipCode) {
	MemberManagement::DorfManagement memberdb = createDb();
	ClubMember member(memberdb);

	member.setZipCode(50512);
	CHECK_EQUAL(50512, member.getZipCode());
}

TEST(City) {
	MemberManagement::DorfManagement memberdb = createDb();
	ClubMember member(memberdb);

	member.setCity("Buxdehude");
	CHECK_EQUAL("Buxdehude", member.getCity());
}

TEST(Id) {
	MemberManagement::DorfManagement memberdb = createDb();
	ClubMember member(memberdb);

	member.setId(42);
	CHECK_EQUAL(42,member.getId());
}

TEST(Date) {
	MemberManagement::DorfManagement memberdb = createDb();
	ClubMember member(memberdb);

	boost::gregorian::greg_year year(2006);
	boost::gregorian::greg_month month(6);
	boost::gregorian::greg_day day(14);
	boost::gregorian::date entryDate(year,month,day);

	member.setEntryDate(entryDate);
	boost::gregorian::date memberDate = member.getEntryDate();

	CHECK_EQUAL(day,memberDate.day());
	CHECK_EQUAL(month,memberDate.month());
	CHECK_EQUAL(year,memberDate.year());
}

TEST(DateOfLeaving) {
	MemberManagement::DorfManagement memberdb = createDb();
	ClubMember member(memberdb);

	boost::gregorian::greg_year year(2006);
	boost::gregorian::greg_month month(10);
	boost::gregorian::greg_day day(13);
	boost::gregorian::date leavingDate(year,month,day);

	member.setLeavingDate(leavingDate);
	boost::gregorian::date memberLeavingDate = member.getLeavingDate();

	CHECK_EQUAL(day,memberLeavingDate.day());
	CHECK_EQUAL(month,memberLeavingDate.month());
	CHECK_EQUAL(year,memberLeavingDate.year());
}

TEST(Info) {
	MemberManagement::DorfManagement memberdb = createDb();
	ClubMember member(memberdb);

	member.setInfo("Bla Test");
	CHECK_EQUAL("Bla Test", member.getInfo());
}

TEST(Deleted) {
	MemberManagement::DorfManagement memberdb = createDb();
	ClubMember member(memberdb);

	member.setDeleted(true);
	CHECK_EQUAL(true, member.getDeleted());
}

TEST(CashCollection) {
	MemberManagement::DorfManagement memberdb = createDb();
	ClubMember member(memberdb);

	member.setCashCollection(true);
	CHECK_EQUAL(true, member.getCashCollection());
}
