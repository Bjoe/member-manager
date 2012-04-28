#include "balancedaotest.h"

#include "model/balancedao.h"

#include <QSqlRecord>
#include <QSqlTableModel>
#include <QModelIndex>

#include "accounting/balanceentry.h"

#include "testconfig.h"
#include "database/databaseutil.h"

#include "model/databasestructure.h"

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

void BalanceDaoTest::testGetMemberBalance()
{
    membermanager::model::BalanceDao balanceDao(QSqlDatabase::database());

    QList<membermanager::accounting::BalanceEntry> balanceList = balanceDao.findByMemberId(1025);

    QCOMPARE(balanceList.size(), 2);

    membermanager::accounting::BalanceEntry balance = balanceList.at(0);
    double value = -15.0;
    QCOMPARE(balance.getValue(), value);

    balance = balanceList.at(1);
    value = 0;
    QCOMPARE(balance.getValue(), value);
}

void BalanceDaoTest::testGetModelByMemberId()
{
    membermanager::model::BalanceDao balanceDao(QSqlDatabase::database());

    QSqlTableModel *model = balanceDao.getModelByMemberId(1025);

    QVERIFY(model);
    QCOMPARE(model->rowCount(), 2);
    QSqlRecord record = model->record(0);
    QCOMPARE(record.value(membermanager::model::SaldoTable::bezeichnung).toString(), QString("Mitgliedsbeitrag Sep"));
    QCOMPARE(record.value(membermanager::model::SaldoTable::betrag).toString(), QString("-15"));
}

void BalanceDaoTest::testInsertNewEmptyRowAndDeletRow()
{
   membermanager::model::BalanceDao balanceDao;

    QSqlTableModel *model = balanceDao.getModelByMemberId(1025);
    QVERIFY(model);
    QCOMPARE(model->rowCount(), 2);

    QModelIndex index = balanceDao.insertNewEmptyRowWithMemberId(1025);

    model->select();
    QCOMPARE(model->rowCount(), 3);
    QCOMPARE(index.row(), 2);

    QVERIFY(balanceDao.deleteRow(index));
    model->select();
    QCOMPARE(model->rowCount(), 2);
}

}
}

QTEST_MAIN(membermanagertest::model::BalanceDaoTest)
#include "balancedaotest.moc"
