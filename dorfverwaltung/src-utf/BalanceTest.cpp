#include <boost/test/unit_test.hpp>
#include "TestFixture.hpp"

#include <boost/date_time/gregorian/gregorian.hpp>
#include <vector>

#include "../src/dorfmanagement.hpp"

#include "../src/Balance.hpp"

using namespace ClubBackend;

BOOST_AUTO_TEST_SUITE(BalanceTest)

BOOST_FIXTURE_TEST_CASE(amount, MemberDB)
{
	Balance balance(database);

	balance.setAmount(12);
	BOOST_CHECK_EQUAL(12,balance.getAmount());
}

BOOST_FIXTURE_TEST_CASE(description, MemberDB)
{
	Balance balance(database);

	balance.setDescription("A Description");
	BOOST_CHECK_EQUAL("A Description",balance.getDescription());
}

BOOST_FIXTURE_TEST_CASE(info, MemberDB)
{
	Balance balance(database);

	balance.setInfo("An Info");
	BOOST_CHECK_EQUAL("An Info",balance.getInfo());
}

BOOST_FIXTURE_TEST_CASE(date, MemberDB)
{
	Balance balance(database);

	boost::gregorian::greg_day day(15);
	boost::gregorian::greg_month month(7);
	boost::gregorian::greg_year year(2006);

	boost::gregorian::date date(year,month,day);

	balance.setDate(date);
	boost::gregorian::date ldate = balance.getDate();

	BOOST_CHECK_EQUAL(day,ldate.day());
	BOOST_CHECK_EQUAL(month,ldate.month());
	BOOST_CHECK_EQUAL(year,ldate.year());
}

BOOST_AUTO_TEST_CASE(GetFieldTypes)
{
	std::vector<litesql::FieldType> fields;
	Balance::getFieldTypes(fields);

	BOOST_CHECK_EQUAL("Balance_.id_",fields[0].fullName());
}

BOOST_FIXTURE_TEST_CASE(withRecords, MemberDB)
{
	litesql::Record record;

	Balance(database,record);
}

BOOST_AUTO_TEST_SUITE_END()
