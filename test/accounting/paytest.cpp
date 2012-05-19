#include "paytest.h"

#include "accounting/pay.h"

#include <QList>
#include <QDate>
#include <QFile>
#include <QTextStream>
#include <QSqlQuery>

#include "dao/memberdao.h"
#include "dao/balancedao.h"
#include "member.h"
#include "accounting/balanceentry.h"
#include "exporter.h"

#include "testconfig.h"
#include "database/databaseutil.h"
#include "dao/databasestructure.h"

namespace membermanagertest {
namespace accounting {

void PayTest::initTestCase()
{
    qttestutil::database::DatabaseUtil database(DATABASEDRIVER);
    database.open(DATABASE);
    database.read(SQLTESTFILE);
}

void PayTest::testPay()
{
    membermanager::accounting::Pay pay("123456","Spasskasse","30050999");

    membermanager::dao::MemberDao dao;

    membermanager::Member member = dao.findByMemberId(1025);
    QDate date(2006,4,1);

    pay.payment(member, "April", date, true);

    QList<double> sum = pay.balancing("DTAUS0.txt");

    double expected = 80.0;
    QCOMPARE(sum.at(0), expected);
    expected = 1.5;
    QCOMPARE(sum.at(1), expected);

    QDate today = QDate::currentDate();

    QFile file("DTAUS0.txt");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        QFAIL("DTAUS cant open");

    QTextStream in(&file);
    QString line = in.readLine();
    QCOMPARE(line, QString("0128ALK3005099900000000SPASSKASSE                 %1    "
                           "00001234560000000000                                               "
                           "10187C30050999090040100012234569000000000000005000 0000000000030050999000012345600000008150"
                           "   KIRK JAMES T                       SPASSKASSE                 1025 MITGLIEDSBEITRAG APRIL1  "
                           "00                                                                     0128E     "
                           "0000001000000000000000000000012234569000000000090040100000000008150"
                           "                                                   ").arg(today.toString("ddMMyy")));
    file.close();


    QString sqlQuery = "SELECT * FROM %1 WHERE %2 = %3 AND %4 = %5 AND %6 = '%7' AND %8 = '%9' AND %10 = '%11'";
    QString select = QString(sqlQuery)
            .arg(membermanager::dao::SaldoTable::TABLENAME)
            .arg(membermanager::dao::SaldoTable::COLUMNNAME[membermanager::dao::SaldoTable::dorfmitglied_pkey])
            .arg(1025)
            .arg(membermanager::dao::SaldoTable::COLUMNNAME[membermanager::dao::SaldoTable::betrag])
            .arg(-80)
            .arg(membermanager::dao::SaldoTable::COLUMNNAME[membermanager::dao::SaldoTable::datum])
            .arg(date.toString(Qt::ISODate))
            .arg(membermanager::dao::SaldoTable::COLUMNNAME[membermanager::dao::SaldoTable::bezeichnung])
            .arg("Mitgliedsbeitrag April")
            .arg(membermanager::dao::SaldoTable::COLUMNNAME[membermanager::dao::SaldoTable::info])
            .arg("Automatische Monats Abbuchung");

    QSqlQuery query;
    QVERIFY(query.exec(select));
    QVERIFY(query.next());

    select = QString(sqlQuery)
            .arg(membermanager::dao::SaldoTable::TABLENAME)
            .arg(membermanager::dao::SaldoTable::COLUMNNAME[membermanager::dao::SaldoTable::dorfmitglied_pkey])
            .arg(1025)
            .arg(membermanager::dao::SaldoTable::COLUMNNAME[membermanager::dao::SaldoTable::betrag])
            .arg(-1.5)
            .arg(membermanager::dao::SaldoTable::COLUMNNAME[membermanager::dao::SaldoTable::datum])
            .arg(date.toString(Qt::ISODate))
            .arg(membermanager::dao::SaldoTable::COLUMNNAME[membermanager::dao::SaldoTable::bezeichnung])
            .arg("Spende April")
            .arg(membermanager::dao::SaldoTable::COLUMNNAME[membermanager::dao::SaldoTable::info])
            .arg("Automatische Monats Abbuchung");

    QVERIFY(query.exec(select));
    QVERIFY(query.next());

    sqlQuery = "SELECT * FROM %1 WHERE %2 = %3 AND %4 = %5 AND %6 = '%7' AND %8 = '%9' AND %10 = '%11' AND %12 = %13";
    select = QString(sqlQuery)
            .arg(membermanager::dao::SaldoTable::TABLENAME)
            .arg(membermanager::dao::SaldoTable::COLUMNNAME[membermanager::dao::SaldoTable::dorfmitglied_pkey])
            .arg(1025)
            .arg(membermanager::dao::SaldoTable::COLUMNNAME[membermanager::dao::SaldoTable::betrag])
            .arg(80)
            .arg(membermanager::dao::SaldoTable::COLUMNNAME[membermanager::dao::SaldoTable::datum])
            .arg(date.toString(Qt::ISODate))
            .arg(membermanager::dao::SaldoTable::COLUMNNAME[membermanager::dao::SaldoTable::bezeichnung])
            .arg("Mitgliedsbeitrag April")
            .arg(membermanager::dao::SaldoTable::COLUMNNAME[membermanager::dao::SaldoTable::info])
            .arg("Automatische Monats Lastschrift")
            .arg(membermanager::dao::SaldoTable::COLUMNNAME[membermanager::dao::SaldoTable::konten])
            .arg(11);

    QVERIFY(query.exec(select));
    QVERIFY(query.next());

    select = QString(sqlQuery)
            .arg(membermanager::dao::SaldoTable::TABLENAME)
            .arg(membermanager::dao::SaldoTable::COLUMNNAME[membermanager::dao::SaldoTable::dorfmitglied_pkey])
            .arg(1025)
            .arg(membermanager::dao::SaldoTable::COLUMNNAME[membermanager::dao::SaldoTable::betrag])
            .arg(1.5)
            .arg(membermanager::dao::SaldoTable::COLUMNNAME[membermanager::dao::SaldoTable::datum])
            .arg(date.toString(Qt::ISODate))
            .arg(membermanager::dao::SaldoTable::COLUMNNAME[membermanager::dao::SaldoTable::bezeichnung])
            .arg("Spende April")
            .arg(membermanager::dao::SaldoTable::COLUMNNAME[membermanager::dao::SaldoTable::info])
            .arg("Automatische Monats Lastschrift")
            .arg(membermanager::dao::SaldoTable::COLUMNNAME[membermanager::dao::SaldoTable::konten])
            .arg(12);

    QVERIFY(query.exec(select));
    QVERIFY(query.next());


}

void PayTest::testPayWithoutBooking()
{
    membermanager::accounting::Pay pay("123456","Spasskasse","30050999");

    membermanager::dao::MemberDao dao;

    membermanager::Member member = dao.findByMemberId(1025);
    QDate date(2006,4,5);

    pay.payment(member, "April", date);

    QList<double> sum = pay.balancing("DTAUS0.txt");

    double expected = 80.0;
    QCOMPARE(sum.at(0), expected);
    expected = 1.5;
    QCOMPARE(sum.at(1), expected);

    QDate today = QDate::currentDate();

    QFile file("DTAUS0.txt");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        QFAIL("DTAUS cant open");

    QTextStream in(&file);
    QString line = in.readLine();
    QCOMPARE(line, QString("0128ALK3005099900000000SPASSKASSE                 %1    "
                           "00001234560000000000                                               "
                           "10187C30050999090040100012234569000000000000005000 0000000000030050999000012345600000008150"
                           "   KIRK JAMES T                       SPASSKASSE                 1025 MITGLIEDSBEITRAG APRIL1  "
                           "00                                                                     0128E     "
                           "0000001000000000000000000000012234569000000000090040100000000008150"
                           "                                                   ").arg(today.toString("ddMMyy")));
    file.close();


    QString sqlQuery = "SELECT * FROM %1 WHERE %2 = %3 AND %4 = %5 AND %6 = '%7' AND %8 = '%9' AND %10 = '%11'";
    QString select = QString(sqlQuery)
            .arg(membermanager::dao::SaldoTable::TABLENAME)
            .arg(membermanager::dao::SaldoTable::COLUMNNAME[membermanager::dao::SaldoTable::dorfmitglied_pkey])
            .arg(1025)
            .arg(membermanager::dao::SaldoTable::COLUMNNAME[membermanager::dao::SaldoTable::betrag])
            .arg(-80)
            .arg(membermanager::dao::SaldoTable::COLUMNNAME[membermanager::dao::SaldoTable::datum])
            .arg(date.toString(Qt::ISODate))
            .arg(membermanager::dao::SaldoTable::COLUMNNAME[membermanager::dao::SaldoTable::bezeichnung])
            .arg("Mitgliedsbeitrag April")
            .arg(membermanager::dao::SaldoTable::COLUMNNAME[membermanager::dao::SaldoTable::info])
            .arg("Automatische Monats Abbuchung");

    QSqlQuery query;
    QVERIFY(query.exec(select));
    QVERIFY(query.next() == false);

    select = QString(sqlQuery)
            .arg(membermanager::dao::SaldoTable::TABLENAME)
            .arg(membermanager::dao::SaldoTable::COLUMNNAME[membermanager::dao::SaldoTable::dorfmitglied_pkey])
            .arg(1025)
            .arg(membermanager::dao::SaldoTable::COLUMNNAME[membermanager::dao::SaldoTable::betrag])
            .arg(-1.5)
            .arg(membermanager::dao::SaldoTable::COLUMNNAME[membermanager::dao::SaldoTable::datum])
            .arg(date.toString(Qt::ISODate))
            .arg(membermanager::dao::SaldoTable::COLUMNNAME[membermanager::dao::SaldoTable::bezeichnung])
            .arg("Spende April")
            .arg(membermanager::dao::SaldoTable::COLUMNNAME[membermanager::dao::SaldoTable::info])
            .arg("Automatische Monats Abbuchung");

    QVERIFY(query.exec(select));
    QVERIFY(query.next() == false);

    sqlQuery = "SELECT * FROM %1 WHERE %2 = %3 AND %4 = %5 AND %6 = '%7' AND %8 = '%9' AND %10 = '%11' AND %12 = %13";
    select = QString(sqlQuery)
            .arg(membermanager::dao::SaldoTable::TABLENAME)
            .arg(membermanager::dao::SaldoTable::COLUMNNAME[membermanager::dao::SaldoTable::dorfmitglied_pkey])
            .arg(1025)
            .arg(membermanager::dao::SaldoTable::COLUMNNAME[membermanager::dao::SaldoTable::betrag])
            .arg(80)
            .arg(membermanager::dao::SaldoTable::COLUMNNAME[membermanager::dao::SaldoTable::datum])
            .arg(date.toString(Qt::ISODate))
            .arg(membermanager::dao::SaldoTable::COLUMNNAME[membermanager::dao::SaldoTable::bezeichnung])
            .arg("Mitgliedsbeitrag April")
            .arg(membermanager::dao::SaldoTable::COLUMNNAME[membermanager::dao::SaldoTable::info])
            .arg("Automatische Monats Lastschrift")
            .arg(membermanager::dao::SaldoTable::COLUMNNAME[membermanager::dao::SaldoTable::konten])
            .arg(11);

    QVERIFY(query.exec(select));
    QVERIFY(query.next() == false);

    select = QString(sqlQuery)
            .arg(membermanager::dao::SaldoTable::TABLENAME)
            .arg(membermanager::dao::SaldoTable::COLUMNNAME[membermanager::dao::SaldoTable::dorfmitglied_pkey])
            .arg(1025)
            .arg(membermanager::dao::SaldoTable::COLUMNNAME[membermanager::dao::SaldoTable::betrag])
            .arg(1.5)
            .arg(membermanager::dao::SaldoTable::COLUMNNAME[membermanager::dao::SaldoTable::datum])
            .arg(date.toString(Qt::ISODate))
            .arg(membermanager::dao::SaldoTable::COLUMNNAME[membermanager::dao::SaldoTable::bezeichnung])
            .arg("Spende April")
            .arg(membermanager::dao::SaldoTable::COLUMNNAME[membermanager::dao::SaldoTable::info])
            .arg("Automatische Monats Lastschrift")
            .arg(membermanager::dao::SaldoTable::COLUMNNAME[membermanager::dao::SaldoTable::konten])
            .arg(12);

    QVERIFY(query.exec(select));
    QVERIFY(query.next() == false);


}

void PayTest::testPaySum()
{
    membermanager::accounting::Pay pay("123456","Spasskasse","30050999");

    membermanager::dao::MemberDao dao;

    membermanager::Member member = dao.findByMemberId(1025);
    QDate date(2006,4,5);

    pay.payment(member, "April", date);
    pay.payment(member, "April", date);

    QList<double> sum = pay.balancing("DTAUS0.txt");

    double expected = 160.0;
    QCOMPARE(sum.at(0), expected);
    expected = 3;
    QCOMPARE(sum.at(1), expected);
}

} // namespace accounting
} // namespace membermanagertest

QTEST_MAIN(membermanagertest::accounting::PayTest)
#include "paytest.moc"
