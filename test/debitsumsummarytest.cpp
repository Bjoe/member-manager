#include "debitsumsummarytest.h"

#include "debitsumsummary.h"

#include "testconfig.h"
#include "database/databaseutil.h"
#include "testutil/summaryhandlermock.h"

namespace membermanagertest
{

void DebitSumSummaryTest::initTestCase()
{
    qttestutil::database::DatabaseUtil database(DATABASEDRIVER);
    database.open(DATABASE);
    database.read(SQLTESTFILE);
}

void DebitSumSummaryTest::testDebitSum()
{
    util::SummaryHandlerMock *handler = new util::SummaryHandlerMock();

    membermanager::DebitSumSummary debitSum(handler);

    QPushButton *button = handler->getPushButton();
    QVERIFY(button);
    QCOMPARE(button->objectName(), QString("debitSumButton"));
    button->click();

    QCOMPARE(handler->getText(), QString("foo"));
}

}

QTEST_MAIN(membermanagertest::DebitSumSummaryTest)
#include "debitsumsummarytest.moc"
