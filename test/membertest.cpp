#include "membertest.h"

#include "member.h"

#include "testconfig.h"
#include "database/databaseutil.h"

namespace ClubFrontendTest
{

void MemberTest::initTestCase()
{
	qttestutil::database::DatabaseUtil database(DATABASEDRIVER);
	database.open(DATABASE);
	database.read(SQLTESTFILE);
}

void MemberTest::testMember()
{
    float donation = 1;
    float fee = 15;
    ClubFrontend::Member member( 1025 );
    QCOMPARE( member.getMemberId(), 1025 );
    QCOMPARE( member.getName(), QString ( "Kirk" ) );
    QCOMPARE( member.getFirstname(), QString ( "James T" ) );
    QCOMPARE( member.getNickname(), QString ( "Capt. Kirk" ) );
    QCOMPARE( member.getEmail(), QString( "fooo@baaar.xx" ));
    QCOMPARE( member.getStreet(), QString( "Industriestr. 23"));
    QCOMPARE( member.getTown(), QString("Bloedeldorf"));
    QCOMPARE( member.getZipCode(), QString("90546"));
    QCOMPARE( member.getAccountNr(), QString("12234569"));
    QCOMPARE( member.getBankName(), QString("sparstrumpf"));
    QCOMPARE( member.getCode(), QString("9004010"));
    QCOMPARE( member.getDonationAsFloat(), donation );
    QCOMPARE( member.getFeeAsFloat(), fee );
    QCOMPARE( member.getContributionInfo(), QString("Beitragsaenderung"));
}

}

QTEST_MAIN ( ClubFrontendTest::MemberTest )
#include "membertest.moc"
