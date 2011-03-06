#include "MemberDaoTest.h"

#include "Model/MemberDao.h"

#include "TestConfig.h"
#include "Model/DatabaseStructure.h"
#include <DatabaseUtils.h>

namespace ClubFrontendTest
{
namespace Model
{

void MemberDaoTest::initTestCase()
{
    TestUtils::Database::DatabaseUtils database ( DATABASEDRIVER );
    database.open ( DATABASE );
    database.read ( SQLTESTFILE );
}

}
}

QTEST_MAIN ( ClubFrontendTest::Model::MemberDaoTest )
#include "MemberDaoTest.moc"
