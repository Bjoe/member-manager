#include "countmembersummarytest.h"

#include "countmembersummary.h"

#include "testconfig.h"
#include "database/databaseutil.h"
#include "testutil/summaryhandlermock.h"

namespace ClubFrontendTest
{

void CountMemberSummaryTest::initTestCase()
{
    qttestutil::database::DatabaseUtil database ( DATABASEDRIVER );
    database.open ( DATABASE );
    database.read ( SQLTESTFILE );
}

void CountMemberSummaryTest::testCountMember()
{
    Utils::SummaryHandlerMock *handler = new Utils::SummaryHandlerMock();

    ClubFrontend::CountMemberSummary countMember ( handler );

    QPushButton *button = handler->getPushButton();
    QVERIFY ( button );
    QCOMPARE ( button->objectName(), QString ( "countMemberButton" ) );
    button->click();

    QCOMPARE ( handler->getText(), QString ( "foo" ) );
}

}

QTEST_MAIN ( ClubFrontendTest::CountMemberSummaryTest )
#include "countmembersummarytest.moc"
