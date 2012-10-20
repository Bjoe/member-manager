
#include <QtTest/QtTest>

#include <QVariant>
#include <QComboBox>
#include <QPushButton>
#include <QHeaderView>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QSqlRecord>
#include <QSqlTableModel>

#include "accounting/balancepersister.h"

#include "testconfig.h"
#include "testcoverageobject.h"
#include "database/databaseutil.h"
#include "dao/databasestructure.h"
#include "dao/balancedao.h"

namespace membermanagertest
{
namespace accounting
{

class BalancePersisterTest : public qttestutil::TestCoverageObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testBook();
};

void BalancePersisterTest::initTestCase()
{
    qttestutil::database::DatabaseUtil database(DATABASEDRIVER);
    database.open(DATABASE);
    database.read(SQLTESTFILE);
}

void BalancePersisterTest::testBook()
{
    QTableWidget *accountingEntryTable = new QTableWidget();
    accountingEntryTable->setColumnCount(9);

    accountingEntryTable->insertRow(0);

    QTableWidgetItem *item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("0")));
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    accountingEntryTable->setItem(0, 0, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("-")));
    accountingEntryTable->setItem(0, 1, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("0")));
    accountingEntryTable->setItem(0, 2, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("0")));
    accountingEntryTable->setItem(0, 3, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("0")));
    accountingEntryTable->setItem(0, 4, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QDate(2012,8,9)));
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    accountingEntryTable->setItem(0, 5, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("530")));
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    accountingEntryTable->setItem(0, 6, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("Miete")));
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    accountingEntryTable->setItem(0, 7, item);

    item = new QTableWidgetItem();
    item->setFlags(Qt::ItemIsUserCheckable);
    item->setCheckState(Qt::Unchecked);
    accountingEntryTable->setItem(0, 8, item);


    accountingEntryTable->insertRow(1);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("1025")));
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    accountingEntryTable->setItem(1, 0, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("Kirk")));
    accountingEntryTable->setItem(1, 1, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("99")));
    accountingEntryTable->setItem(1, 2, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("1.5")));
    accountingEntryTable->setItem(1, 3, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("0")));
    accountingEntryTable->setItem(1, 4, item);

    item = new QTableWidgetItem();
    item->setData(Qt::UserRole, QVariant(123456));
    item->setData(Qt::DisplayRole, QVariant(QDate(2012,8,10)));
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    accountingEntryTable->setItem(1, 5, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("100.5")));
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    accountingEntryTable->setItem(1, 6, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("Mitgliedsbeitrag")));
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    accountingEntryTable->setItem(1, 7, item);

    item = new QTableWidgetItem();
    item->setFlags(Qt::ItemIsUserCheckable);
    item->setCheckState(Qt::Unchecked);
    accountingEntryTable->setItem(1, 8, item);

    membermanager::dao::BalanceDao balanceDao;
    QSqlTableModel *balanceTableModel = balanceDao.getModelByMemberId(1025);
    QCOMPARE(balanceTableModel->rowCount(), 15);

    membermanager::accounting::BalancePersister balancePersister(accountingEntryTable);
    balancePersister.booking();

    using membermanager::dao::SaldoTable;
    balanceTableModel->setSort(SaldoTable::saldo_pkey, Qt::DescendingOrder);
    balanceTableModel->select();
    QCOMPARE(balanceTableModel->rowCount(), 17);

    QSqlRecord record = balanceTableModel->record(0);
    float value = 1.5;
    QCOMPARE(record.value(SaldoTable::betrag).toFloat(), value);
    value = 12;
    QCOMPARE(record.value(SaldoTable::konten - 1).toFloat(), value);
    QCOMPARE(record.value(SaldoTable::kasse_pkey - 1).toInt(), 123456);

    record = balanceTableModel->record(1);
    value = 99;
    QCOMPARE(record.value(SaldoTable::betrag).toFloat(), value);
    value = 11;
    QCOMPARE(record.value(SaldoTable::konten - 1).toFloat(), value);
    QCOMPARE(record.value(SaldoTable::kasse_pkey - 1).toInt(), 123456);

    item = accountingEntryTable->item(1, 8);
    QVERIFY(item->checkState() == Qt::Checked);
}

} // namespace accounting
} // namespace membermanagertest


QTEST_MAIN(membermanagertest::accounting::BalancePersisterTest)
#include "moc_balancepersistertest.cxx"
