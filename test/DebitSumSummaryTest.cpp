#include "DebitSumSummaryTest.h"

#include "DebitSumSummary.h"

#include "TestConfig.h"
#include <DatabaseUtils.h>
#include "TestUtils/SummaryHandlerMock.h"

namespace ClubFrontendTest
{

void DebitSumSummaryTest::initTestCase()
{
    TestUtils::Database::DatabaseUtils database ( DATABASEDRIVER );
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
#include "DebitSumSummaryTest.moc"
