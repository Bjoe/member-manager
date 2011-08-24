#include "debitsumsummarytest.h"

#include "debitsumsummary.h"

#include "testconfig.h"
#include "database/databaseutil.h"
#include "testutil/summaryhandlermock.h"

namespace ClubFrontendTest
{

void DebitSumSummaryTest::initTestCase()
{
    qttestutil::database::DatabaseUtil database ( DATABASEDRIVER );
    database.open ( DATABASE );
    database.read ( SQLTESTFILE );
}

void DebitSumSummaryTest::testDebitSum()
{
    Utils::SummaryHandlerMock *handler = new Utils::SummaryHandlerMock();

    ClubFrontend::DebitSumSummary debitSum ( handler );

    QPushButton *button = handler->getPushButton();
    QVERIFY ( button );
    QCOMPARE ( button->objectName(), QString ( "debitSumButton" ) );
    button->click();

    QCOMPARE ( handler->getText(), QString ( "foo" ) );
}

}

QTEST_MAIN ( ClubFrontendTest::DebitSumSummaryTest )
#include "debitsumsummarytest.moc"
