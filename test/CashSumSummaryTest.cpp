#include "CashSumSummaryTest.h"

#include "CashSumSummary.h"

#include "TestUtils/SummaryHandlerMock.h"

#include "TestConfig.h"
#include <DatabaseUtils.h>

namespace ClubFrontendTest
{

void CashSumSummaryTest::initTestCase()
{
    TestUtils::Database::DatabaseUtils database ( DATABASEDRIVER );
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
#include "CashSumSummaryTest.moc"
