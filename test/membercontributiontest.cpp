#include "membercontributiontest.h"

#include "membercontribution.h"

#include <QSqlQuery>
#include "testconfig.h"
#include "database/databaseutil.h"
#include "model/databasestructure.h"

namespace membermanagertest
{

void MemberContributionTest::initTestCase()
{
    qttestutil::database::DatabaseUtil database(DATABASEDRIVER);
    database.open(DATABASE);
    database.read(SQLTESTFILE);
}

void MemberContributionTest::testGetContribution()
{
    using membermanager::model::MemberFilter;
    MemberFilter filter = MemberFilter::build().withMemberId(1025);

    double fee = 15;
    double donation = 1;
    membermanager::MemberContribution memberContribution(filter);
    QCOMPARE(memberContribution.getFee(), fee);
    QCOMPARE(memberContribution.getDonation(), donation);
    QCOMPARE(memberContribution.getInfo(), QString("Beitragsaenderung"));
    QCOMPARE(memberContribution.getValidFrom(), QDate(2007, 5, 1));
}

void MemberContributionTest::testSaveContribution()
{
    using membermanager::model::MemberFilter;
    MemberFilter filter = MemberFilter::build().withMemberId(1025);

    double fee = 15;
    double donation = 1;
    membermanager::MemberContribution memberContribution(filter);
    QCOMPARE(memberContribution.getFee(), fee);
    QCOMPARE(memberContribution.getDonation(), donation);
    QCOMPARE(memberContribution.getInfo(), QString("Beitragsaenderung"));
    QCOMPARE(memberContribution.getValidFrom(), QDate(2007, 5, 1));

    memberContribution.setFee(42);
    memberContribution.setDonation(23);
    memberContribution.setInfo(QString("More stuff"));
    memberContribution.setValidFrom(QDate(2007, 7, 14));

    QVERIFY(memberContribution.save());

    int id = 1025;
    using membermanager::model::MemberTable;
    using membermanager::model::ContributionTable;
    const QString whereClause = QString(" where %1=%2 order by %3 desc").arg(
                                    MemberTable::COLUMNNAME[MemberTable::MemberId])
                                .arg(id).arg(ContributionTable::ValidFrom);
    QSqlQuery query("select * from " + ContributionTable::TABLENAME + whereClause);
    query.exec();
    query.last();
    QCOMPARE(query.value(ContributionTable::Fee).toInt(), 42);
    QCOMPARE(query.value(ContributionTable::Donation).toInt(), 23);
    QCOMPARE(query.value(ContributionTable::Info).toString(), QString("More stuff"));
    QCOMPARE(query.value(ContributionTable::ValidFrom).toString(), QString("2007-07-14"));
}

void MemberContributionTest::testSaveNewContribution()
{
    using membermanager::model::MemberFilter;
    MemberFilter filter = MemberFilter::build().withMemberId(1025);

    double fee = 42;
    double donation = 23;
    membermanager::MemberContribution memberContribution(filter);
    QCOMPARE(memberContribution.getFee(), fee);
    QCOMPARE(memberContribution.getDonation(), donation);
    QCOMPARE(memberContribution.getInfo(), QString("More stuff"));
    QCOMPARE(memberContribution.getValidFrom(), QDate(2007, 7, 14));

    memberContribution.setFee(99);
    memberContribution.setDonation(55);
    memberContribution.setInfo(QString("New stuff"));
    memberContribution.setValidFrom(QDate(2009, 10, 15));


    int id = 1025;
    using membermanager::model::MemberTable;
    using membermanager::model::ContributionTable;
    const QString whereClause = QString(" where %1=%2 order by %3 desc").arg(
                                    MemberTable::COLUMNNAME[MemberTable::MemberId])
                                .arg(id).arg(ContributionTable::ValidFrom);
    QSqlQuery query("select * from " + ContributionTable::TABLENAME + whereClause);
    query.exec();
    QVERIFY(query.next());
    QVERIFY(query.next());
    QVERIFY(!query.next());

    QVERIFY(memberContribution.saveNewRecord());
    query.exec();
    QVERIFY(query.next());
    QVERIFY(query.next());
    QVERIFY(query.next());
    QVERIFY(!query.next());

    query.exec();
    query.last();
    QCOMPARE(query.value(ContributionTable::Fee).toInt(), 99);
    QCOMPARE(query.value(ContributionTable::Donation).toInt(), 55);
    QCOMPARE(query.value(ContributionTable::Info).toString(), QString("New stuff"));
    QCOMPARE(query.value(ContributionTable::ValidFrom).toString(), QString("2009-10-15"));
}

}

QTEST_MAIN(membermanagertest::MemberContributionTest)
#include "membercontributiontest.moc"
