#include "MemberTest.h"

#include "Model/Member.h"

namespace ClubFrontendTest
{

void MemberTest::testDefaultKonstruktor()
{
    ClubFrontend::Member member;
}

void MemberTest::testMember()
{
    float donation = 2.5;
    float fee = 1.5;
    ClubFrontend::Member member ( 1, "name", "firstname", "nickname",
                                  donation, fee );
    QCOMPARE ( member.getMemberId(), 1 );
    QCOMPARE ( member.getName(), QString ( "name" ) );
    QCOMPARE ( member.getFirstname(), QString ( "firstname" ) );
    QCOMPARE ( member.getNickname(), QString ( "nickname" ) );
    QCOMPARE ( member.getDonation(), donation );
    QCOMPARE ( member.getFee(), fee );
}

}

QTEST_MAIN ( ClubFrontendTest::MemberTest )
#include "MemberTest.moc"
