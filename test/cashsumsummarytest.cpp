#include "cashsumsummarytest.h"

#include "cashsumsummary.h"

#include "testutil/summaryhandlermock.h"

#include "testconfig.h"
#include "database/databaseutil.h"

namespace ClubFrontendTest
{

void CashSumSummaryTest::initTestCase()
{
    qttestutil::database::DatabaseUtil database ( DATABASEDRIVER );
    database.open ( DATABASE );
    database.read ( SQLTESTFILE );
}

void CashSumSummaryTest::testCashSum()
{
    Utils::SummaryHandlerMock *handler = new Utils::SummaryHandlerMock();

    ClubFrontend::CashSumSummary cashSum ( handler );

    QPushButton *button = handler->getPushButton();
    QVERIFY ( button );
    QCOMPARE ( button->objectName(), QString ( "cashSumButton" ) );
    button->click();

    QCOMPARE ( handler->getText(), QString ( "foo" ) );
}

}

QTEST_MAIN ( ClubFrontendTest::CashSumSummaryTest )
#include "cashsumsummarytest.moc"
