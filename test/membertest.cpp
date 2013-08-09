#include "membertest.h"

#include "member.h"

#include "dao/memberdao.h"

#include "testconfig.h"
#include "database/databaseutil.h"

namespace membermanagertest
{

void MemberTest::initTestCase()
{
    qttestutil::database::DatabaseUtil database(DATABASEDRIVER);
    database.open(DATABASE);
    database.read(SQLTESTFILE);
}

void MemberTest::testGetMember()
{
    membermanager::dao::MemberDao memberDao(QSqlDatabase::database());
    membermanager::Member member = memberDao.findByMemberId(1025);

    QCOMPARE(member.getMemberId(), 1025);
    QCOMPARE(member.getName(), QString("Kirk"));
    QCOMPARE(member.getFirstname(), QString("James T"));
    QCOMPARE(member.getNickname(), QString("Capt. Kirk"));
    QCOMPARE(member.getEntryDate(), QDate(2001, 4, 24));
    QCOMPARE(member.getReference(), QString("2193"));
    QCOMPARE(member.getInfo(), QString("Captain of the ncc-1701"));
    QCOMPARE(member.getEmail(), QString("fooo@baaar.xx"));
    QCOMPARE(member.getStreet(), QString("Industriestr. 23"));
    QCOMPARE(member.getCity(), QString("Bloedeldorf"));
    QCOMPARE(member.getZipCode(), QString("90546"));
    QCOMPARE(member.getAccountNr(), QString("12234569"));
    QCOMPARE(member.getBankName(), QString("sparstrumpf"));
    QCOMPARE(member.getCode(), QString("9004010"));
    QVERIFY(member.isCollection() == true);
    QVERIFY(member.isDeleted() == false);
}

void MemberTest::testSetMember()
{
    membermanager::dao::MemberDao memberDao(QSqlDatabase::database());
    membermanager::Member member = memberDao.findByMemberId(1025);

    member.setName("Archer");
    member.setFirstname("Jonathan");
    member.setNickname("Captain");
    member.setStreet("NCC-1701");
    member.setCity("Dtown");
    member.setZipCode("98765");
    member.setEmail("foo@bar.tx");
    member.setEntryDate(QDate(2006, 07, 15));
    member.setAccountNr("123456789");
    member.setBankName("Galaxy");
    member.setCode("98765432");
    member.setInfo("Lalala");
    member.setReference("9876");
    member.setCollection(false);
    member.setDeleted(true);

    QCOMPARE(member.getMemberId(), 1025);
    QCOMPARE(member.getName(), QString("Archer"));
    QCOMPARE(member.getFirstname(), QString("Jonathan"));
    QCOMPARE(member.getNickname(), QString("Captain"));
    QCOMPARE(member.getEntryDate(), QDate(2006, 7, 15));
    QCOMPARE(member.getInfo(), QString("Lalala"));
    QCOMPARE(member.getEmail(), QString("foo@bar.tx"));
    QCOMPARE(member.getStreet(), QString("NCC-1701"));
    QCOMPARE(member.getCity(), QString("Dtown"));
    QCOMPARE(member.getZipCode(), QString("98765"));
    QCOMPARE(member.getAccountNr(), QString("123456789"));
    QCOMPARE(member.getBankName(), QString("Galaxy"));
    QCOMPARE(member.getCode(), QString("98765432"));
    QCOMPARE(member.getReference(), QString("9876"));
    QVERIFY(member.isCollection() == false);
    QVERIFY(member.isDeleted() == true);
}

}

QTEST_MAIN(membermanagertest::MemberTest)
#include "moc_membertest.cpp"
