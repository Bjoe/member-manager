#include "memberfactorytest.h"

#include "memberfactory.h"

#include "member.h"
#include "testconfig.h"
#include "database/databaseutil.h"

namespace membermanagertest
{

void MemberFactoryTest::initTestCase()
{
    qttestutil::database::DatabaseUtil database(DATABASEDRIVER);
    database.open(DATABASE);
    database.read(SQLTESTFILE);
}

void MemberFactoryTest::testCreateNewMember()
{
    membermanager::Member member = membermanager::MemberFactory::createNewMember();
    QCOMPARE(member.getMemberId(), 1027);
}

void MemberFactoryTest::testCreateExistsMember()
{
    membermanager::Member member = membermanager::MemberFactory::createMember(1025);
    QCOMPARE(member.getMemberId(), 1025);
}

}

QTEST_MAIN(membermanagertest::MemberFactoryTest)
#include "memberfactorytest.moc"
