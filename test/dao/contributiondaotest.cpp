#include "contributiondaotest.h"

#include "dao/contributiondao.h"

#include <QDate>
#include <QSqlRecord>
#include <QSqlTableModel>

#include "accounting/contributionentry.h"

#include "dao/databasestructure.h"

#include "testconfig.h"
#include "database/databaseutil.h"

using membermanager::dao::ContributionDao;
using membermanager::dao::ContributionTable;
using membermanager::accounting::ContributionEntry;

namespace membermanagertest {
namespace dao {

void ContributionDaoTest::initTestCase()
{
    qttestutil::database::DatabaseUtil database(DATABASEDRIVER);
    database.open(DATABASE);
    database.read(SQLTESTFILE);
}

void ContributionDaoTest::testSaveNewRecord()
{
    ContributionDao contributionDao(QSqlDatabase::database());
    QVERIFY(contributionDao.saveRecord(ContributionEntry(1)));
}

void ContributionDaoTest::testSaveRecord()
{
    ContributionDao contributionDao(QSqlDatabase::database());
    ContributionEntry entry = contributionDao.findLastDateByMemberId(1025);

    QVERIFY(contributionDao.saveRecord(entry));
}

void ContributionDaoTest::testFindByMemberIdWithPointInTime()
{
    ContributionDao contributionDao(QSqlDatabase::database());

    ContributionEntry entry = contributionDao.findByMemberIdWithPointInTime(1025, QDate(2007, 04, 12));

    double fee = 14.00;
    QCOMPARE(entry.getFee(), fee);
}

void ContributionDaoTest::testFindLastDateByMemberId()
{
    ContributionDao contributionDao(QSqlDatabase::database());

    ContributionEntry entry = contributionDao.findLastDateByMemberId(1025);

    double fee = 99.00;
    QCOMPARE(entry.getFee(), fee);
}

void ContributionDaoTest::testGetModelByMemberId()
{
    ContributionDao contributionDao(QSqlDatabase::database());

    const QSqlTableModel *model = contributionDao.getModelByMemberId(1025);

    QVERIFY(model);
    QCOMPARE(model->rowCount(), 7);
    QSqlRecord record = model->record(0);
    QCOMPARE(record.value(ContributionTable::Info).toString(), QString("Beitragsaenderung"));
    QCOMPARE(record.value(ContributionTable::Fee).toString(), QString("99"));
}

void ContributionDaoTest::testInsertNewEmptyRowAndDeletRow()
{
    ContributionDao contributionDao;

    QSqlTableModel *model = contributionDao.getModelByMemberId(1025);
    QVERIFY(model);
    QCOMPARE(model->rowCount(), 7);

    QModelIndex index = contributionDao.insertNewEmptyRowWithMemberId(1025);

    QCOMPARE(index.row(), 7);
    model->select();
    QCOMPARE(model->rowCount(), 8);

    QVERIFY(contributionDao.deleteRow(index));

    model->select();
    QCOMPARE(model->rowCount(), 7);
}

} // namespace model
} // namespace membermanagertest

QTEST_MAIN(membermanagertest::dao::ContributionDaoTest)
#include "contributiondaotest.moc"
