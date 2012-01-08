#include "membertest.h"

#include "member.h"

#include "membercontribution.h"
#include "model/memberfilter.h"

#include <QSqlQuery>
#include "model/databasestructure.h"
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
    using membermanager::model::MemberFilter;
    MemberFilter filter = MemberFilter::build().withMemberId(1025);
    membermanager::Member member(filter);
    QCOMPARE(member.getMemberId(), 1025);
    QCOMPARE(member.getName(), QString("Kirk"));
    QCOMPARE(member.getFirstname(), QString("James T"));
    QCOMPARE(member.getNickname(), QString("Capt. Kirk"));
    QCOMPARE(member.getEntryDate(), QDate(2001, 4, 24));
    QCOMPARE(member.getInfo(), QString("Captain of the ncc-1701"));
    QCOMPARE(member.getEmail(), QString("fooo@baaar.xx"));
    QCOMPARE(member.getStreet(), QString("Industriestr. 23"));
    QCOMPARE(member.getCity(), QString("Bloedeldorf"));
    QCOMPARE(member.getZipCode(), QString("90546"));
    QCOMPARE(member.getAccountNr(), QString("12234569"));
    QCOMPARE(member.getBankName(), QString("sparstrumpf"));
    QCOMPARE(member.getCode(), QString("9004010"));
    QVERIFY(member.isDeleted() == false);
}

void MemberTest::testGetMembercontribution()
{
    using membermanager::model::MemberFilter;
    MemberFilter filter = MemberFilter::build().withMemberId(1025);
    membermanager::Member member(filter);
    membermanager::MemberContribution memberContribution = member.getMemberContribution();

    double fee = 15;
    QCOMPARE(memberContribution.getFee(), fee);
}

void MemberTest::testSaveMember()
{
    using membermanager::model::MemberFilter;
    MemberFilter filter = MemberFilter::build().withMemberId(1025);
    membermanager::Member member(filter);
    QCOMPARE(member.getMemberId(), 1025);
    QCOMPARE(member.getName(), QString("Kirk"));
    QCOMPARE(member.getFirstname(), QString("James T"));
    QCOMPARE(member.getNickname(), QString("Capt. Kirk"));
    QCOMPARE(member.getEntryDate(), QDate(2001, 4, 24));
    QCOMPARE(member.getInfo(), QString("Captain of the ncc-1701"));
    QCOMPARE(member.getEmail(), QString("fooo@baaar.xx"));
    QCOMPARE(member.getStreet(), QString("Industriestr. 23"));
    QCOMPARE(member.getCity(), QString("Bloedeldorf"));
    QCOMPARE(member.getZipCode(), QString("90546"));
    QCOMPARE(member.getAccountNr(), QString("12234569"));
    QCOMPARE(member.getBankName(), QString("sparstrumpf"));
    QCOMPARE(member.getCode(), QString("9004010"));
    QVERIFY(member.isDeleted() == false);

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
    member.setDeleted(true);

    QVERIFY(member.save());

    const QString whereClause(" where dorfmitglied_pkey=1025");

    using membermanager::model::MemberTable;
    QSqlQuery query;
    query.exec("select * from " + MemberTable::TABLENAME + whereClause);
    query.next();
    QCOMPARE(query.value(MemberTable::FirstName).toString(), QString("Jonathan"));
    QCOMPARE(query.value(MemberTable::Name).toString(), QString("Archer"));
    QCOMPARE(query.value(MemberTable::NickName).toString(), QString("Captain"));
    QCOMPARE(query.value(MemberTable::Info).toString(), QString("Lalala"));
    QVERIFY(query.value(MemberTable::Deleted).toBool());

    using membermanager::model::AddressTable;
    query.exec("select * from " + AddressTable::TABLENAME + whereClause);
    query.next();
    QCOMPARE(query.value(AddressTable::Street).toString(), QString("NCC-1701"));
    QCOMPARE(query.value(AddressTable::ZipCode).toString(), QString("98765"));
    QCOMPARE(query.value(AddressTable::Town).toString(), QString("Dtown"));

    using membermanager::model::BankAccountTable;
    query.exec("select * from " + BankAccountTable::TABLENAME + whereClause);
    query.next();
    QCOMPARE(query.value(BankAccountTable::Code).toInt(), 98765432);
    QCOMPARE(query.value(BankAccountTable::AccountNr).toInt(), 123456789);
    QCOMPARE(query.value(BankAccountTable::BankName).toString(), QString("Galaxy"));

    using membermanager::model::RessourcenTable;
    query.exec("select * from " + RessourcenTable::TABLENAME + whereClause);
    query.next();
    QCOMPARE(query.value(RessourcenTable::EmailAdress).toString(), QString("foo@bar.tx"));
}

}

QTEST_MAIN(membermanagertest::MemberTest)
#include "membertest.moc"
