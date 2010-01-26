#include <boost/test/unit_test.hpp>
#include "TestFixture.hpp"

#include <iostream>

#include "../src/dorfmanagement.hpp"
#include "../src/ClubMember.hpp"
#include "../src/Balance.hpp"
#include "../src/VillageSquare.hpp"

using namespace ClubBackend;

BOOST_AUTO_TEST_SUITE(VillageSquareTest)

BOOST_FIXTURE_TEST_CASE(SortedBySurename, MemberDB)
{
    VillageSquare square(database);

    std::vector<ClubMember> clubmember = square.sortedBySurename();

    unsigned int i = 2;
    BOOST_CHECK_EQUAL(i,clubmember.size());
    BOOST_CHECK_EQUAL("Kirk",clubmember[0].getName());
    BOOST_CHECK_EQUAL("Solo",clubmember[1].getName());
    BOOST_CHECK_EQUAL(1024,clubmember[1].getId());
}

BOOST_FIXTURE_TEST_CASE(SortedByFirstname, MemberDB)
{
    VillageSquare square(database);

    std::vector<ClubMember> clubmember = square.sortedByFirstname();

    unsigned int i = 2;
    BOOST_CHECK_EQUAL(i,clubmember.size());
    BOOST_CHECK_EQUAL("Han",clubmember[0].getFirstname());
    BOOST_CHECK_EQUAL("James Tiberius",clubmember[1].getFirstname());
    BOOST_CHECK_EQUAL(1024,clubmember[0].getId());
}

BOOST_FIXTURE_TEST_CASE(SortedByMemberId, MemberDB)
{
    VillageSquare square(database);

    std::vector<ClubMember> clubmember = square.sortedByMemberId();

    unsigned int i = 2;
    BOOST_CHECK_EQUAL(i,clubmember.size());
    BOOST_CHECK_EQUAL("Kirk",clubmember[0].getName());
    BOOST_CHECK_EQUAL("Solo",clubmember[1].getName());
    BOOST_CHECK_EQUAL(1024,clubmember[1].getId());
}

BOOST_FIXTURE_TEST_CASE(SortedByNickname, MemberDB)
{
    VillageSquare square(database);

    std::vector<ClubMember> clubmember = square.sortedByNickname();

    unsigned int i = 2;
    BOOST_CHECK_EQUAL(i,clubmember.size());
    BOOST_CHECK_EQUAL("Captain",clubmember[0].getNickname());
    BOOST_CHECK_EQUAL("Wokii",clubmember[1].getNickname());
    BOOST_CHECK_EQUAL(1024,clubmember[1].getId());
}

BOOST_FIXTURE_TEST_CASE(GetDeleted, MemberDB)
{
    VillageSquare square(database);

    std::vector<ClubMember> clubmember = square.getDeletedMembers();

    unsigned int i = 1;
    BOOST_CHECK_EQUAL(i,clubmember.size());
    BOOST_CHECK_EQUAL("Bond",clubmember[0].getName());
}

BOOST_FIXTURE_TEST_CASE(GetMember, MemberDB)
{
    VillageSquare square(database);

    ClubMember clubmember = square.getMember(1024);

    BOOST_CHECK_EQUAL("Solo",clubmember.getName());
}

BOOST_FIXTURE_TEST_CASE(GetMemberCashAccount, MemberDB)
{
    VillageSquare square(database);

    try {
        std::vector<Balance> balance = square.getMemberCashAccount(1024);
        BOOST_CHECK_EQUAL(42,balance[0].getAmount());
    } catch(litesql::Except& except) {
        std::cout << except << std::endl;
    }

}

BOOST_AUTO_TEST_SUITE_END()
