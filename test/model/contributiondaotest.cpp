#include "contributiondaotest.h"

#include "model/contributiondao.h"

#include <QSqlRecord>

#include "accounting/contributionentry.h"

#include "testconfig.h"
#include "database/databaseutil.h"

namespace membermanagertest {
namespace model {

void ContributionDaoTest::initTestCase()
{
    qttestutil::database::DatabaseUtil database(DATABASEDRIVER);
    database.open(DATABASE);
    database.read(SQLTESTFILE);
}

void ContributionDaoTest::testSaveDao()
{
    membermanager::model::ContributionDao contributionDao(QSqlDatabase::database());
    QVERIFY(contributionDao.saveRecord(membermanager::accounting::ContributionEntry(1)));
}

} // namespace model
} // namespace membermanagertest

QTEST_MAIN(membermanagertest::model::ContributionDaoTest)
#include "contributiondaotest.moc"
