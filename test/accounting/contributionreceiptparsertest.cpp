
#include <QtTest/QtTest>

#include <QObject>
#include <QList>
#include <QDate>
#include <QIODevice>
#include <QTextStream>

#include "entity/member.h"
#include "entity/balance.h"

#include "accounting/contributionreceiptparser.h"

namespace test {
namespace accounting {

class ContributionReceiptParserTest : public QObject
{
    Q_OBJECT

private slots:
    void testReplaceName();
    void testReplaceFirstname();
    void testReplaceStreet();
    void testReplaceCity();
    void testReplaceFromDate();
    void testReplaceToDate();
    void testReplaceSum();
    void testReplaceText();
    void testReplaceLine();
};

void ContributionReceiptParserTest::testReplaceName()
{
    QList<QObject *> list;

    membermanager::entity::Member* member = new membermanager::entity::Member();
    member->setName("foobar");

    membermanager::accounting::ContributionReceiptParser parser(65.0, 2013, &list, member);

    QString in;
    in.append("la Mustermann la");
    QTextStream inStream;
    inStream.setString(&in, QIODevice::ReadOnly);

    QString out;
    QTextStream outStream;
    outStream.setString(&out, QIODevice::WriteOnly);

    parser.parse(inStream, outStream);

    QCOMPARE(out, QString("la foobar la\n"));

    delete member;
}

void ContributionReceiptParserTest::testReplaceFirstname()
{
    QList<QObject *> list;

    membermanager::entity::Member* member = new membermanager::entity::Member();
    member->setFirstname("foobar");

    membermanager::accounting::ContributionReceiptParser parser(65.0, 2013, &list, member);

    QString in;
    in.append("la Mustername la");
    QTextStream inStream;
    inStream.setString(&in, QIODevice::ReadOnly);

    QString out;
    QTextStream outStream;
    outStream.setString(&out, QIODevice::WriteOnly);

    parser.parse(inStream, outStream);

    QCOMPARE(out, QString("la foobar la\n"));

    delete member;
}

void ContributionReceiptParserTest::testReplaceStreet()
{
    QList<QObject *> list;

    membermanager::entity::Member* member = new membermanager::entity::Member();
    member->setStreet("foobar 42");

    membermanager::accounting::ContributionReceiptParser parser(65.0, 2013, &list, member);

    QString in;
    in.append("la Musterstraße 23 la");
    QTextStream inStream;
    inStream.setString(&in, QIODevice::ReadOnly);

    QString out;
    QTextStream outStream;
    outStream.setString(&out, QIODevice::WriteOnly);

    parser.parse(inStream, outStream);

    QCOMPARE(out, QString("la foobar 42 la\n"));

    delete member;
}

void ContributionReceiptParserTest::testReplaceCity()
{
    QList<QObject *> list;

    membermanager::entity::Member* member = new membermanager::entity::Member();
    member->setCity("foobar");
    member->setZipCode("23456");

    membermanager::accounting::ContributionReceiptParser parser(65.0, 2013, &list, member);

    QString in;
    in.append("la 12345 Musterstadt la");
    QTextStream inStream;
    inStream.setString(&in, QIODevice::ReadOnly);

    QString out;
    QTextStream outStream;
    outStream.setString(&out, QIODevice::WriteOnly);

    parser.parse(inStream, outStream);

    QCOMPARE(out, QString("la 23456 foobar la\n"));

    delete member;
}

void ContributionReceiptParserTest::testReplaceFromDate()
{
    QList<QObject *> list;
    membermanager::entity::Member* member = new membermanager::entity::Member();

    membermanager::accounting::ContributionReceiptParser parser(65.0, 2013, &list, member);

    QString in;
    in.append("la 11.11.1111 la");
    QTextStream inStream;
    inStream.setString(&in, QIODevice::ReadOnly);

    QString out;
    QTextStream outStream;
    outStream.setString(&out, QIODevice::WriteOnly);

    parser.parse(inStream, outStream);

    QCOMPARE(out, QString("la 01.01.2013 la\n"));

    delete member;
}

void ContributionReceiptParserTest::testReplaceToDate()
{
    QList<QObject *> list;
    membermanager::entity::Member* member = new membermanager::entity::Member();

    membermanager::accounting::ContributionReceiptParser parser(65.0, 2013, &list, member);

    QString in;
    in.append("la 99.99.9999 la");
    QTextStream inStream;
    inStream.setString(&in, QIODevice::ReadOnly);

    QString out;
    QTextStream outStream;
    outStream.setString(&out, QIODevice::WriteOnly);

    parser.parse(inStream, outStream);

    QCOMPARE(out, QString("la 31.12.2013 la\n"));

    delete member;
}

void ContributionReceiptParserTest::testReplaceSum()
{
    membermanager::entity::Balance* balance1 = new membermanager::entity::Balance();
    membermanager::entity::Balance* balance2 = new membermanager::entity::Balance();

    balance1->setValue(23.00);
    balance2->setValue(42.00);

    QList<QObject *> list;
    list.append(balance1);
    list.append(balance2);

    membermanager::entity::Member* member = new membermanager::entity::Member();

    membermanager::accounting::ContributionReceiptParser parser(65.0, 2013, &list, member);

    QString in;
    in.append("la 23,00 la");
    QTextStream inStream;
    inStream.setString(&in, QIODevice::ReadOnly);

    QString out;
    QTextStream outStream;
    outStream.setString(&out, QIODevice::WriteOnly);

    parser.parse(inStream, outStream);

    QCOMPARE(out, QString("la   65,00 la\n"));

    delete member;
    delete balance1;
    delete balance2;
}

void ContributionReceiptParserTest::testReplaceText()
{
    membermanager::entity::Balance* balance1 = new membermanager::entity::Balance();
    membermanager::entity::Balance* balance2 = new membermanager::entity::Balance();

    balance1->setValue(23.00);
    balance2->setValue(42.00);

    QList<QObject *> list;
    list.append(balance1);
    list.append(balance2);

    membermanager::entity::Member* member = new membermanager::entity::Member();

    membermanager::accounting::ContributionReceiptParser parser(65.0, 2013, &list, member);

    QString in;
    in.append("la DREIUNDZWANZIG la");
    QTextStream inStream;
    inStream.setString(&in, QIODevice::ReadOnly);

    QString out;
    QTextStream outStream;
    outStream.setString(&out, QIODevice::WriteOnly);

    parser.parse(inStream, outStream);

    QCOMPARE(out, QString("la \\Huge{Bitte ausfuellen} la\n"));

    delete member;
    delete balance1;
    delete balance2;
}

void ContributionReceiptParserTest::testReplaceLine()
{
    membermanager::entity::Balance* balance1 = new membermanager::entity::Balance();
    membermanager::entity::Balance* balance2 = new membermanager::entity::Balance();

    balance1->setValuta(QDate(2013, 4, 15));
    balance1->setValue(23.00);
    balance1->setPurpose("Beitrag");

    balance2->setValuta(QDate(2013, 10, 3));
    balance2->setValue(42.00);
    balance2->setPurpose("Spende");

    QList<QObject *> list;
    list.append(balance1);
    list.append(balance2);

    membermanager::entity::Member* member = new membermanager::entity::Member();

    membermanager::accounting::ContributionReceiptParser parser(65.0, 2013, &list, member);

    QString in;
    in.append("88.88.8888 & 99,00 Euro & Mitgliedsbeitrag oder Geldzuwendugen");
    QTextStream inStream;
    inStream.setString(&in, QIODevice::ReadOnly);

    QString out;
    QTextStream outStream;
    outStream.setString(&out, QIODevice::WriteOnly);

    parser.parse(inStream, outStream);

    QCOMPARE(out, QString("15.04.2013 &   23,00 Euro & Beitrag\\\\\n"
                          "03.10.2013 &   42,00 Euro & Spende\\\\\n"));

    delete member;
    delete balance1;
    delete balance2;
}

}
}

QTEST_MAIN(test::accounting::ContributionReceiptParserTest)
#include "moc_contributionreceiptparsertest.cpp"

