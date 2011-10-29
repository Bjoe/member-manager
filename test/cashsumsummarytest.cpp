#include "cashsumsummarytest.h"

#include "cashsumsummary.h"

#include "testutil/summaryhandlermock.h"

#include "testconfig.h"
#include "database/databaseutil.h"

namespace membermanagertest
{

void CashSumSummaryTest::initTestCase()
{
    qttestutil::database::DatabaseUtil database(DATABASEDRIVER);
    database.open(DATABASE);
    database.read(SQLTESTFILE);
}

void CashSumSummaryTest::testCashSum()
{
    util::SummaryHandlerMock *handler = new util::SummaryHandlerMock();

    membermanager::CashSumSummary cashSum(handler);

    QPushButton *button = handler->getPushButton();
    QVERIFY(button);
    QCOMPARE(button->objectName(), QString("cashSumButton"));
    button->click();

    QCOMPARE(handler->getText(), QString("foo"));
}

}

QTEST_MAIN(membermanagertest::CashSumSummaryTest)
#include "cashsumsummarytest.moc"
