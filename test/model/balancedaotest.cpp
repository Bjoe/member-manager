#include "balancedaotest.h"

#include "model/balancedao.h"

#include <QSqlRecord>

#include "accounting/balanceentry.h"

#include "testconfig.h"
#include "database/databaseutil.h"

namespace membermanagertest
{
namespace model
{

void BalanceDaoTest::initTestCase()
{
    qttestutil::database::DatabaseUtil database(DATABASEDRIVER);
    database.open(DATABASE);
    database.read(SQLTESTFILE);
}

void BalanceDaoTest::testSaveBalance()
{
    membermanager::model::BalanceDao balanceDao(QSqlDatabase::database());
    QVERIFY(balanceDao.saveRecord(membermanager::accounting::BalanceEntry(1)));
}

}
}

QTEST_MAIN(membermanagertest::model::BalanceDaoTest)
#include "balancedaotest.moc"
