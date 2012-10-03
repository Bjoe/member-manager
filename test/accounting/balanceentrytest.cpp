#include "balanceentrytest.h"

#include "accounting/balanceentry.h"

#include <QDate>

#include "dao/balancedao.h"

namespace membermanagertest
{
namespace accounting
{

void BalanceEntryTest::testCreateEntry()
{
    QDate date = QDate::currentDate();

    membermanager::accounting::BalanceEntry balanceEntry(1);
    balanceEntry.setValue(15);
    balanceEntry.setValuta(date);
    balanceEntry.setAccount(10);
    balanceEntry.setInfo("foo");
    balanceEntry.setPurpose("bar");
    balanceEntry.setCashKey(12345);

    QCOMPARE(balanceEntry.getMemberId(), 1);
    double value = 15.00;
    QCOMPARE(balanceEntry.getValue(), value);
    QCOMPARE(balanceEntry.getValuta(), date);
    QCOMPARE(balanceEntry.getAccount(), 10);
    QCOMPARE(balanceEntry.getInfo(), QString("foo"));
    QCOMPARE(balanceEntry.getPurpose(), QString("bar"));
    QCOMPARE(balanceEntry.getCashKey(), 12345);
}

}
}

QTEST_MAIN(membermanagertest::accounting::BalanceEntryTest)
#include "balanceentrytest.moc"
