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
#include "dtaus/exporter.h"

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

    QList<double> sum = pay.balancing("DTAUS0");

    double expected = 80.0;
    QCOMPARE(sum.at(0), expected);
    expected = 1.5;
    QCOMPARE(sum.at(1), expected);
    expected = 0;
    QCOMPARE(sum.at(2), expected);

    QDate today = QDate::currentDate();

    QFile file("DTAUS0.txt");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        QFAIL("DTAUS cant open");

    QTextStream in(&file);
    QString line = in.readLine();
    QCOMPARE(line, QString("0128ALK3005099900000000SPASSKASSE                 %1    "
                           "00001234560000000000                                               "
                           "10245C30050999090040100012234569000000000000005000 0000000000030050999000012345600000008150"
                           "   KIRK JAMES T                       SPASSKASSE                 1025 MITGLIEDSBEITRAG APRIL1  "
                           "020280,00 EUR UND SPENDE  1,50 02EUR                                   0128E     "
                           "0000001000000000000000000000012234569000000000090040100000000008150"
                           "                                                   ").arg(today.toString("ddMMyy")));
    file.close();

    QFile csvFile("DTAUS0.csv");
    if(!csvFile.open(QIODevice::ReadOnly | QIODevice::Text))
        QFAIL("DTAUS.csv cant open");

    QTextStream csvIn(&csvFile);

    line = csvIn.readLine();
    QCOMPARE(line, QString("01.04.2006;Lastschrift Einzug 011;011 Mitgliedsbeitrag Kirk James T;80"));
    line = csvIn.readLine();
    QCOMPARE(line, QString("01.04.2006;Lastschrift Einzug 012;012 Spende Kirk James T;1.5"));
    QVERIFY(csvIn.atEnd());

    QString sqlQuery = "SELECT * FROM %1 WHERE %2 = %3 AND %4 = %5 AND %6 = '%7' AND %8 = '%9' AND %10 = '%11' AND %12 = %13";
    QString select = QString(sqlQuery)
            .arg(membermanager::dao::BalanceTable::TABLENAME)
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::MemberId])
            .arg(1025)
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::Amount])
            .arg(-80)
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::Date])
            .arg(date.toString(Qt::ISODate))
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::Description])
            .arg("Mitgliedsbeitrag April")
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::Info])
            .arg("Automatische Monats Abbuchung")
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::BookingAccount])
            .arg(-11);

    QSqlQuery query;
    QVERIFY(query.exec(select));
    QVERIFY(query.next());

    select = QString(sqlQuery)
            .arg(membermanager::dao::BalanceTable::TABLENAME)
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::MemberId])
            .arg(1025)
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::Amount])
            .arg(-1.5)
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::Date])
            .arg(date.toString(Qt::ISODate))
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::Description])
            .arg("Spende April")
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::Info])
            .arg("Automatische Monats Abbuchung")
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::BookingAccount])
            .arg(-12);

    QVERIFY(query.exec(select));
    QVERIFY(query.next());

    select = QString(sqlQuery)
            .arg(membermanager::dao::BalanceTable::TABLENAME)
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::MemberId])
            .arg(1025)
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::Amount])
            .arg(80)
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::Date])
            .arg(date.toString(Qt::ISODate))
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::Description])
            .arg("Mitgliedsbeitrag April")
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::Info])
            .arg("Automatische Monats Lastschrift")
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::BookingAccount])
            .arg(11);

    QVERIFY(query.exec(select));
    QVERIFY(query.next());

    select = QString(sqlQuery)
            .arg(membermanager::dao::BalanceTable::TABLENAME)
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::MemberId])
            .arg(1025)
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::Amount])
            .arg(1.5)
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::Date])
            .arg(date.toString(Qt::ISODate))
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::Description])
            .arg("Spende April")
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::Info])
            .arg("Automatische Monats Lastschrift")
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::BookingAccount])
            .arg(12);

    QVERIFY(query.exec(select));
    QVERIFY(query.next());
}

void PayTest::testAdditionalPay()
{
    membermanager::accounting::Pay pay("123456","Spasskasse","30050999");

    membermanager::dao::MemberDao dao;

    membermanager::Member member = dao.findByMemberId(1025);
    QDate date(2007,4,1);

    pay.payment(member, "April", date, true);

    QList<double> sum = pay.balancing("DTAUS0");

    double expected = 14.0;
    QCOMPARE(sum.at(0), expected);
    expected = 1;
    QCOMPARE(sum.at(1), expected);
    expected = 5;
    QCOMPARE(sum.at(2), expected);

    QDate today = QDate::currentDate();

    QFile file("DTAUS0.txt");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        QFAIL("DTAUS cant open");

    QTextStream in(&file);
    QString line = in.readLine();
    QCOMPARE(line, QString("0128ALK3005099900000000SPASSKASSE                 %1    "
                           "00001234560000000000                                               "
                           "10274C30050999090040100012234569000000000000005000 0000000000030050999000012345600000002000"
                           "   KIRK JAMES T                       SPASSKASSE                 1025 MITGLIEDSBEITRAG APRIL1  "
                           "030214,00 EUR UND SPENDE  1,00 02EUR UND CCC BEITRAG  5,00 E           02UR                                                                                                                            0128E     "
                           "0000001000000000000000000000012234569000000000090040100000000002000"
                           "                                                   ").arg(today.toString("ddMMyy")));
    file.close();

    QFile csvFile("DTAUS0.csv");
    if(!csvFile.open(QIODevice::ReadOnly | QIODevice::Text))
        QFAIL("DTAUS.csv cant open");

    QTextStream csvIn(&csvFile);

    line = csvIn.readLine();
    QCOMPARE(line, QString("01.04.2007;Lastschrift Einzug 011;011 Mitgliedsbeitrag Kirk James T;14"));
    line = csvIn.readLine();
    QCOMPARE(line, QString("01.04.2007;Lastschrift Einzug 012;012 Spende Kirk James T;1"));
    line = csvIn.readLine();
    QCOMPARE(line, QString("01.04.2007;Lastschrift Einzug 004;004 Durchlaufender Posten / CCC Beitrag Kirk James T;5"));
    QVERIFY(csvIn.atEnd());

    QString sqlQuery = "SELECT * FROM %1 WHERE %2 = %3 AND %4 = %5 AND %6 = '%7' AND %8 = '%9' AND %10 = '%11'";
    QString select = QString(sqlQuery)
            .arg(membermanager::dao::BalanceTable::TABLENAME)
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::MemberId])
            .arg(1025)
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::Amount])
            .arg(-14)
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::Date])
            .arg(date.toString(Qt::ISODate))
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::Description])
            .arg("Mitgliedsbeitrag April")
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::Info])
            .arg("Automatische Monats Abbuchung");

    QSqlQuery query;
    QVERIFY(query.exec(select));
    QVERIFY(query.next());

    select = QString(sqlQuery)
            .arg(membermanager::dao::BalanceTable::TABLENAME)
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::MemberId])
            .arg(1025)
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::Amount])
            .arg(-1)
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::Date])
            .arg(date.toString(Qt::ISODate))
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::Description])
            .arg("Spende April")
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::Info])
            .arg("Automatische Monats Abbuchung");

    QVERIFY(query.exec(select));
    QVERIFY(query.next());

    select = QString(sqlQuery)
            .arg(membermanager::dao::BalanceTable::TABLENAME)
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::MemberId])
            .arg(1025)
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::Amount])
            .arg(-5)
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::Date])
            .arg(date.toString(Qt::ISODate))
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::Description])
            .arg("CCC Beitrag April")
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::Info])
            .arg("Automatische Monats Abbuchung");

    QVERIFY(query.exec(select));
    QVERIFY(query.next());

    sqlQuery = "SELECT * FROM %1 WHERE %2 = %3 AND %4 = %5 AND %6 = '%7' AND %8 = '%9' AND %10 = '%11' AND %12 = %13";
    select = QString(sqlQuery)
            .arg(membermanager::dao::BalanceTable::TABLENAME)
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::MemberId])
            .arg(1025)
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::Amount])
            .arg(14)
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::Date])
            .arg(date.toString(Qt::ISODate))
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::Description])
            .arg("Mitgliedsbeitrag April")
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::Info])
            .arg("Automatische Monats Lastschrift")
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::BookingAccount])
            .arg(11);

    QVERIFY(query.exec(select));
    QVERIFY(query.next());

    select = QString(sqlQuery)
            .arg(membermanager::dao::BalanceTable::TABLENAME)
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::MemberId])
            .arg(1025)
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::Amount])
            .arg(1)
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::Date])
            .arg(date.toString(Qt::ISODate))
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::Description])
            .arg("Spende April")
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::Info])
            .arg("Automatische Monats Lastschrift")
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::BookingAccount])
            .arg(12);

    QVERIFY(query.exec(select));
    QVERIFY(query.next());

    select = QString(sqlQuery)
            .arg(membermanager::dao::BalanceTable::TABLENAME)
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::MemberId])
            .arg(1025)
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::Amount])
            .arg(5)
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::Date])
            .arg(date.toString(Qt::ISODate))
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::Description])
            .arg("CCC Beitrag April")
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::Info])
            .arg("Automatische Monats Lastschrift")
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::BookingAccount])
            .arg(4);

    QVERIFY(query.exec(select));
    QVERIFY(query.next());
}

void PayTest::testPayWithoutBooking()
{
    membermanager::accounting::Pay pay("123456","Spasskasse","30050999");

    membermanager::dao::MemberDao dao;

    membermanager::Member member = dao.findByMemberId(1030);
    QDate date(2006,4,5);

    pay.payment(member, "April", date);

    QList<double> sum = pay.balancing("DTAUS0");

    double expected = 80.0;
    QCOMPARE(sum.at(0), expected);
    expected = 0.0;
    QCOMPARE(sum.at(1), expected);
    QCOMPARE(sum.at(2), expected);

    QDate today = QDate::currentDate();

    QFile dtausFile("DTAUS0.txt");
    if(!dtausFile.open(QIODevice::ReadOnly | QIODevice::Text))
        QFAIL("DTAUS.txt cant open");

    QTextStream dtausIn(&dtausFile);
    QString line = dtausIn.readLine();
    QCOMPARE(line, QString("0128ALK3005099900000000SPASSKASSE                 %1    "
                           "00001234560000000000                                               "
                           "10216C30050999029402840000019779000000000000005000 0000000000030050999000012345600000008000"
                           "   SCOTT MONTGOMERY                   SPASSKASSE                 1030 MITGLIEDSBEITRAG APRIL1  "
                           "010280,00 EUR                                                          0128E     "
                           "0000001000000000000000000000000019779000000000029402840000000008000"
                           "                                                   ").arg(today.toString("ddMMyy")));
    dtausFile.close();

    QFile csvFile("DTAUS0.csv");
    if(!csvFile.open(QIODevice::ReadOnly | QIODevice::Text))
        QFAIL("DTAUS.csv cant open");

    QTextStream csvIn(&csvFile);

    line = csvIn.readLine();
    QCOMPARE(line, QString("05.04.2006;Lastschrift Einzug 011;011 Mitgliedsbeitrag Scott Montgomery;80"));
    QVERIFY(csvIn.atEnd());

    QString sqlQuery = "SELECT * FROM %1 WHERE %2 = %3 AND %4 = %5 AND %6 = '%7' AND %8 = '%9' AND %10 = '%11'";
    QString select = QString(sqlQuery)
            .arg(membermanager::dao::BalanceTable::TABLENAME)
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::MemberId])
            .arg(1030)
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::Amount])
            .arg(-80)
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::Date])
            .arg(date.toString(Qt::ISODate))
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::Description])
            .arg("Mitgliedsbeitrag April")
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::Info])
            .arg("Automatische Monats Abbuchung");

    QSqlQuery query;
    QVERIFY(query.exec(select));
    QVERIFY(query.next() == false);

    select = QString(sqlQuery)
            .arg(membermanager::dao::BalanceTable::TABLENAME)
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::MemberId])
            .arg(1030)
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::Amount])
            .arg(0.0)
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::Date])
            .arg(date.toString(Qt::ISODate))
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::Description])
            .arg("Spende April")
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::Info])
            .arg("Automatische Monats Abbuchung");

    QVERIFY(query.exec(select));
    QVERIFY(query.next() == false);

    sqlQuery = "SELECT * FROM %1 WHERE %2 = %3 AND %4 = %5 AND %6 = '%7' AND %8 = '%9' AND %10 = '%11' AND %12 = %13";
    select = QString(sqlQuery)
            .arg(membermanager::dao::BalanceTable::TABLENAME)
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::MemberId])
            .arg(1030)
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::Amount])
            .arg(80)
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::Date])
            .arg(date.toString(Qt::ISODate))
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::Description])
            .arg("Mitgliedsbeitrag April")
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::Info])
            .arg("Automatische Monats Lastschrift")
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::BookingAccount])
            .arg(11);

    QVERIFY(query.exec(select));
    QVERIFY(query.next() == false);

    select = QString(sqlQuery)
            .arg(membermanager::dao::BalanceTable::TABLENAME)
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::MemberId])
            .arg(1030)
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::Amount])
            .arg(0.0)
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::Date])
            .arg(date.toString(Qt::ISODate))
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::Description])
            .arg("Spende April")
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::Info])
            .arg("Automatische Monats Lastschrift")
            .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::BookingAccount])
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

    QList<double> sum = pay.balancing("DTAUS0");

    double expected = 160.0;
    QCOMPARE(sum.at(0), expected);
    expected = 3;
    QCOMPARE(sum.at(1), expected);
}

} // namespace accounting
} // namespace membermanagertest

QTEST_MAIN(membermanagertest::accounting::PayTest)
#include "moc_paytest.cpp"
