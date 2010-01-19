#include <boost/test/unit_test.hpp>
#include "TestFixture.hpp"

#include <vector>
#include <boost/date_time/gregorian/gregorian.hpp>
#include "../src/dorfmanagement.hpp"

#include "../src/Contribution.hpp"

using namespace Dorfverwaltung;

BOOST_AUTO_TEST_SUITE(ContributionTest)

BOOST_FIXTURE_TEST_CASE(Fee, MemberDB)
{
    Contribution contribution(database);

    contribution.setFee(6);
    BOOST_CHECK_EQUAL(6,contribution.getFee());
}

BOOST_FIXTURE_TEST_CASE(Donation, MemberDB)
{
    Contribution contribution(database);

    contribution.setDonation(23);
    BOOST_CHECK_EQUAL(23,contribution.getDonation());
}

BOOST_FIXTURE_TEST_CASE(Info, MemberDB)
{
    Contribution contribution(database);

    contribution.setInfo("Info Text");
    BOOST_CHECK_EQUAL("Info Text",contribution.getInfo());
}

BOOST_FIXTURE_TEST_CASE(ValidFrom, MemberDB)
{
    Contribution contribution(database);

    boost::gregorian::greg_year year(2006);
    boost::gregorian::greg_month month(6);
    boost::gregorian::greg_day day(14);
    boost::gregorian::date validFrom(year,month,day);

    contribution.setValidFrom(validFrom);
    boost::gregorian::date lvalidFrom = contribution.getValidFrom();

    BOOST_CHECK_EQUAL(day,lvalidFrom.day());
    BOOST_CHECK_EQUAL(month,lvalidFrom.month());
    BOOST_CHECK_EQUAL(year,lvalidFrom.year());
}

BOOST_AUTO_TEST_CASE(GetFieldTypes)
{
    std::vector<litesql::FieldType> fields;
    Contribution::getFieldTypes(fields);

    BOOST_CHECK_EQUAL("Contribution_.id_",fields[0].fullName());
}

BOOST_FIXTURE_TEST_CASE(withRecords, MemberDB)
{
    litesql::Record record;

    Contribution(database, record);
}

BOOST_AUTO_TEST_SUITE_END()
