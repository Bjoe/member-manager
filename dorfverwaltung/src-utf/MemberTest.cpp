#include <boost/test/unit_test.hpp>

#include "TestFixture.hpp"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <litesql.hpp>
#include <vector>

#include "../src/EMail.hpp"

#include "../src/dorfmanagement.hpp"
#include "../src/Member.hpp"

using namespace ClubBackend;

BOOST_AUTO_TEST_SUITE(MemberTest)

BOOST_FIXTURE_TEST_CASE(Name, MemberDB)
{
	Member member(database);

	member.setName("Kirk");
	BOOST_CHECK_EQUAL("Kirk",member.getName());
}

BOOST_FIXTURE_TEST_CASE(FirstName, MemberDB)
{
	Member member(database);

	member.setFirstname("james");
	BOOST_CHECK_EQUAL("james",member.getFirstname());
}

BOOST_FIXTURE_TEST_CASE(NickName, MemberDB)
{
	Member member(database);

	member.setNickname("jamesT");
	BOOST_CHECK_EQUAL("jamesT",member.getNickname());
}

BOOST_FIXTURE_TEST_CASE(Email, MemberDB)
{
	Member member(database);

	EMail::EMail email("archer@enterprise.gl");

	member.setEmail(email);
	BOOST_CHECK_EQUAL("archer@enterprise.gl", member.getEmail().getAddress());
}

BOOST_FIXTURE_TEST_CASE(Street, MemberDB)
{
	Member member(database);

	member.setStreet("Bunsenhausen");
	BOOST_CHECK_EQUAL("Bunsenhausen", member.getStreet());
}

BOOST_FIXTURE_TEST_CASE(ZipCode, MemberDB)
{
	Member member(database);

	member.setZipCode(50512);
	BOOST_CHECK_EQUAL(50512, member.getZipCode());
}

BOOST_FIXTURE_TEST_CASE(City, MemberDB)
{
	Member member(database);

	member.setCity("Buxdehude");
	BOOST_CHECK_EQUAL("Buxdehude", member.getCity());
}

BOOST_FIXTURE_TEST_CASE(Id, MemberDB)
{
	Member member(database);

	member.setId(42);
	BOOST_CHECK_EQUAL(42,member.getId());
}

BOOST_FIXTURE_TEST_CASE(Date, MemberDB)
{
	Member member(database);

	boost::gregorian::greg_year year(2006);
	boost::gregorian::greg_month month(6);
	boost::gregorian::greg_day day(14);
	boost::gregorian::date entryDate(year,month,day);

	member.setEntryDate(entryDate);
	boost::gregorian::date memberDate = member.getEntryDate();

	BOOST_CHECK_EQUAL(day,memberDate.day());
	BOOST_CHECK_EQUAL(month,memberDate.month());
	BOOST_CHECK_EQUAL(year,memberDate.year());
}

BOOST_FIXTURE_TEST_CASE(DateOfLeaving, MemberDB)
{
	Member member(database);

	boost::gregorian::greg_year year(2006);
	boost::gregorian::greg_month month(10);
	boost::gregorian::greg_day day(13);
	boost::gregorian::date leavingDate(year,month,day);

	member.setLeavingDate(leavingDate);
	boost::gregorian::date memberLeavingDate = member.getLeavingDate();

	BOOST_CHECK_EQUAL(day,memberLeavingDate.day());
	BOOST_CHECK_EQUAL(month,memberLeavingDate.month());
	BOOST_CHECK_EQUAL(year,memberLeavingDate.year());
}

BOOST_FIXTURE_TEST_CASE(Info, MemberDB)
{
	Member member(database);

	member.setInfo("Bla Test");
	BOOST_CHECK_EQUAL("Bla Test", member.getInfo());
}

BOOST_FIXTURE_TEST_CASE(Deleted, MemberDB)
{
	Member member(database);

	member.setDeleted(true);
	BOOST_CHECK_EQUAL(true, member.getDeleted());
}

BOOST_FIXTURE_TEST_CASE(CashCollection, MemberDB)
{
	Member member(database);

	member.setCashCollection(true);
	BOOST_CHECK_EQUAL(true, member.getCashCollection());
}

BOOST_AUTO_TEST_CASE(GetFieldTypes)
{
	std::vector<litesql::FieldType> fields;
	Member::getFieldTypes(fields);

	BOOST_CHECK_EQUAL("Member_.id_",fields[0].fullName());
}

BOOST_FIXTURE_TEST_CASE(WithRecords, MemberDB)
{
	litesql::Record record;

	Member(database,record);
}

BOOST_FIXTURE_TEST_CASE(Money, MemberDB)
{
	Member member(database);

	MemberManagement::Member::MoneyHandle money = member.money();
}

BOOST_FIXTURE_TEST_CASE(Ressourcen, MemberDB)
{
	Member member(database);

	MemberManagement::Member::InternalRessourcenHandle ressourcen = member.internalRessourcen();
}

BOOST_FIXTURE_TEST_CASE(BankAccount, MemberDB)
{
	Member member(database);

	MemberManagement::Member::BankAccountHandle bankAccount = member.bankAccount();
}

BOOST_FIXTURE_TEST_CASE(CashAccount, MemberDB)
{
	Member member(database);

	MemberManagement::Member::CashAccountHandle cashAccount = member.cashAccount();
}

BOOST_AUTO_TEST_SUITE_END()
