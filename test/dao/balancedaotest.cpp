#include "balancedaotest.h"

#include "dao/balancedao.h"

#include <QSqlRecord>
#include <QSqlTableModel>
#include <QModelIndex>
#include <QDate>

#include "accounting/balanceentry.h"

#include "testconfig.h"
#include "database/databaseutil.h"

#include "dao/databasestructure.h"

namespace membermanagertest
{
namespace dao
{

void BalanceDaoTest::initTestCase()
{
    qttestutil::database::DatabaseUtil database(DATABASEDRIVER);
    database.open(DATABASE);
    database.read(SQLTESTFILE);
}

void BalanceDaoTest::testSaveBalance()
{
    membermanager::dao::BalanceDao balanceDao(QSqlDatabase::database());
    QVERIFY(balanceDao.saveRecord(membermanager::accounting::BalanceEntry(1)));
}

void BalanceDaoTest::testGetMemberBalance()
{
    membermanager::dao::BalanceDao balanceDao(QSqlDatabase::database());

    QList<membermanager::accounting::BalanceEntry> balanceList = balanceDao.findByMemberId(1025);

    QCOMPARE(balanceList.size(), 15);

    membermanager::accounting::BalanceEntry balance = balanceList.at(0);
    double value = 8.0;
    QCOMPARE(balance.getValue(), value);

    balance = balanceList.at(1);
    value = -5;
    QCOMPARE(balance.getValue(), value);
}

void BalanceDaoTest::testGetModelByMemberId()
{
    membermanager::dao::BalanceDao balanceDao(QSqlDatabase::database());

    QSqlTableModel *model = balanceDao.getModelByMemberId(1025);

    QVERIFY(model);
    QCOMPARE(model->rowCount(), 15);
    QSqlRecord record = model->record(0);
    QCOMPARE(record.value(membermanager::dao::SaldoTable::bezeichnung).toString(), QString("ZAHLUNGSEINGANG  1025 Ali Baba MITGLIEDSSCHULDEN"));
    QCOMPARE(record.value(membermanager::dao::SaldoTable::betrag).toString(), QString("8"));
}

void BalanceDaoTest::testFindContributionByMemberIdAndYear()
{
    membermanager::dao::BalanceDao balanceDao(QSqlDatabase::database());

    QList<membermanager::accounting::BalanceEntry> balanceList = balanceDao.findContributionByMemberIdAndYear(1025, 2007);

    QCOMPARE(balanceList.size(), 4);

    membermanager::accounting::BalanceEntry balance = balanceList.at(0);
    double value = 15.0;
    QCOMPARE(balance.getValue(), value);
    QCOMPARE(balance.getValuta(), QDate(2007,3,8));

    balance = balanceList.at(3);
    value = 10;
    QCOMPARE(balance.getValue(), value);
    QCOMPARE(balance.getValuta(), QDate(2007,4,5));
}

void BalanceDaoTest::testInsertNewEmptyRowAndDeletRow()
{
   membermanager::dao::BalanceDao balanceDao;

    QSqlTableModel *model = balanceDao.getModelByMemberId(1025);
    QVERIFY(model);
    QCOMPARE(model->rowCount(), 15);

    QModelIndex index = balanceDao.insertNewEmptyRowWithMemberId(1025);

    model->select();
    QCOMPARE(model->rowCount(), 16);
    QCOMPARE(index.row(), 15);

    QVERIFY(balanceDao.deleteRow(index));
    model->select();
    QCOMPARE(model->rowCount(), 15);
}

}
}

QTEST_MAIN(membermanagertest::dao::BalanceDaoTest)
#include "balancedaotest.moc"
