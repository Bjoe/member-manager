
#include <QtTest/QtTest>

#include <QDateTime>

#include "accounting/statemententry.h"

#include "testconfig.h"
#include "testcoverageobject.h"

namespace membermanagertest
{
namespace accounting
{

class StatementEntryTest : public qttestutil::TestCoverageObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testEntry();
};

void StatementEntryTest::initTestCase()
{
}

void StatementEntryTest::testEntry()
{
    membermanager::accounting::StatementEntry statementEntry(1);
    QDateTime today = QDateTime::currentDateTime();
    statementEntry.setDate(today);
    statementEntry.setDeleted(true);
    statementEntry.setBooked(false);
    statementEntry.setMemberId(12345);
    statementEntry.setPrimanota("abc987");
    statementEntry.setPurpose("test text");
    statementEntry.setRemoteAccountNumber("987654321");
    statementEntry.setRemoteBankCode("10020030");
    statementEntry.setRemoteName("Hans Mustermann");
    statementEntry.setTransactionCode(23);
    statementEntry.setTransactionText("Action");
    statementEntry.setValue(100.99);
    QDateTime now = QDateTime::currentDateTime();
    statementEntry.setValuta(now);

    QCOMPARE(statementEntry.getId(), 1);
    QCOMPARE(statementEntry.getDate(), today);
    QCOMPARE(statementEntry.isDeleted(), true);
    QCOMPARE(statementEntry.getMemberId(), 12345);
    QCOMPARE(statementEntry.getPrimanota(), QString("abc987"));
    QCOMPARE(statementEntry.getPurpose(), QString("test text"));
    QCOMPARE(statementEntry.getRemoteAccountNumber(), QString("987654321"));
    QCOMPARE(statementEntry.getRemoteBankCode(), QString("10020030"));
    QCOMPARE(statementEntry.getRemoteName(), QString("Hans Mustermann"));
    QCOMPARE(statementEntry.getTransactionCode(), 23);
    QCOMPARE(statementEntry.getTransactionText(), QString("Action"));
    double value = 100.99;
    QCOMPARE(statementEntry.getValue(), value);
    QCOMPARE(statementEntry.getValuta(), now);
}

} // namespace accounting
} // namespace membermanagertest


QTEST_MAIN(membermanagertest::accounting::StatementEntryTest)
#include "moc_statemententrytest.cpp"

