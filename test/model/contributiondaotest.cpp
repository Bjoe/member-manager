#include "contributiondaotest.h"

#include "model/contributiondao.h"

#include <QDate>
#include <QSqlRecord>

#include "accounting/contributionentry.h"

#include "testconfig.h"
#include "database/databaseutil.h"

using membermanager::model::ContributionDao;
using membermanager::accounting::ContributionEntry;

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
    ContributionDao contributionDao(QSqlDatabase::database());
    QVERIFY(contributionDao.saveRecord(ContributionEntry(1)));
}

void ContributionDaoTest::testGetEntry()
{
    ContributionDao contributionDao(QSqlDatabase::database());

    ContributionEntry entry = contributionDao.findByMemberIdWithPointInTime(1025, QDate(2007, 04, 12));

    double fee = 14.00;
    QCOMPARE(entry.getFee(), fee);
}

} // namespace model
} // namespace membermanagertest

QTEST_MAIN(membermanagertest::model::ContributionDaoTest)
#include "contributiondaotest.moc"
