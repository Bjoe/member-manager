#include <boost/test/unit_test.hpp>
#include "TestFixture.hpp"

#include <vector>

#include "../src/dorfmanagement.hpp"

#include "../src/Bank.hpp"

using namespace Dorfverwaltung;

BOOST_AUTO_TEST_SUITE(BankTest)

BOOST_FIXTURE_TEST_CASE(Account, MemberDB)
{
    Bank::Bank bank(database);

    bank.setAccount(123456);
    BOOST_CHECK_EQUAL(123456,bank.getAccount());
}

BOOST_FIXTURE_TEST_CASE(Name, MemberDB)
{
    Bank::Bank bank(database);

    bank.setName("ssk");
    BOOST_CHECK_EQUAL("ssk",bank.getName());
}


BOOST_FIXTURE_TEST_CASE(Code, MemberDB)
{
    Bank::Bank bank(database);

    bank.setCode(30050110);
    BOOST_CHECK_EQUAL(30050110,bank.getCode());
}

BOOST_AUTO_TEST_CASE(GetFieldTypes)
{
    std::vector<litesql::FieldType> fields;
    Bank::getFieldTypes(fields);

    BOOST_CHECK_EQUAL("Bank_.id_",fields[0].fullName());
}

BOOST_FIXTURE_TEST_CASE(WithRecord, MemberDB)
{
    litesql::Record record;

    Bank(database, record);
}

BOOST_AUTO_TEST_SUITE_END()
