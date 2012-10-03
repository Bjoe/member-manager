#include "accountingentryimporterviewtest.h"

#include "gui/accountingentryimporterview.h"

#include <QVariant>
#include <QComboBox>
#include <QPushButton>
#include <QHeaderView>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QSqlRecord>
#include <QSqlTableModel>

#include "testconfig.h"
#include "database/databaseutil.h"
#include "dao/databasestructure.h"
#include "dao/balancedao.h"

namespace membermanagertest
{
namespace gui
{

void AccountingEntryImporterViewTest::initTestCase()
{
    qttestutil::database::DatabaseUtil database(DATABASEDRIVER);
    database.open(DATABASE);
    database.read(SQLTESTFILE);
}

void AccountingEntryImporterViewTest::testImport()
{
    membermanager::gui::AccountingEntryImporterView accountingEntryImportView;

    QTableWidget *tableWidget = accountingEntryImportView.findChild<QTableWidget *>("tableWidget");

    QCOMPARE(tableWidget->columnCount(), 8);
    QHeaderView *headerView = tableWidget->horizontalHeader();
    QCOMPARE(headerView->count(), 8);
    QCOMPARE(tableWidget->rowCount(), 2);
    QVERIFY(tableWidget->itemDelegateForColumn(1));

    QTableWidgetItem *item = tableWidget->item(0, 0);
    QVariant variant = item->data(Qt::DisplayRole);
    QVERIFY((item->flags() & Qt::ItemIsEditable) == false);
    QCOMPARE(variant.toString(), QString("0"));

    item = tableWidget->item(0, 1);
    variant = item->data(Qt::DisplayRole);
    QVERIFY(item->flags() & Qt::ItemIsEditable);
    QCOMPARE(variant.toString(), QString("-"));

    item = tableWidget->item(0, 2);
    variant = item->data(Qt::DisplayRole);
    QVERIFY(item->flags() & Qt::ItemIsEditable);
    QCOMPARE(variant.toString(), QString("0"));

    item = tableWidget->item(0, 3);
    variant = item->data(Qt::DisplayRole);
    QVERIFY(item->flags() & Qt::ItemIsEditable);
    QCOMPARE(variant.toString(), QString("0"));

    item = tableWidget->item(0, 4);
    variant = item->data(Qt::DisplayRole);
    QVERIFY(item->flags() & Qt::ItemIsEditable);
    QCOMPARE(variant.toString(), QString("0"));

    item = tableWidget->item(0, 5);
    variant = item->data(Qt::DisplayRole);
    QVERIFY((item->flags() & Qt::ItemIsEditable) == false);
    QCOMPARE(variant.toDate(), QDate(2012,8,9));

    item = tableWidget->item(0, 6);
    variant = item->data(Qt::DisplayRole);
    QVERIFY((item->flags() & Qt::ItemIsEditable) == false);
    QCOMPARE(variant.toString(), QString("530"));

    item = tableWidget->item(0, 7);
    variant = item->data(Qt::DisplayRole);
    QVERIFY((item->flags() & Qt::ItemIsEditable) == false);
    QCOMPARE(variant.toString(), QString("Miete"));




    item = tableWidget->item(1, 0);
    variant = item->data(Qt::DisplayRole);
    QVERIFY((item->flags() & Qt::ItemIsEditable) == false);
    QCOMPARE(variant.toString(), QString("1025"));

    item = tableWidget->item(1, 1);
    variant = item->data(Qt::DisplayRole);
    QVERIFY(item->flags() & Qt::ItemIsEditable);
    QCOMPARE(variant.toString(), QString("Kirk"));

    item = tableWidget->item(1, 2);
    variant = item->data(Qt::DisplayRole);
    QVERIFY(item->flags() & Qt::ItemIsEditable);
    QCOMPARE(variant.toString(), QString("99"));

    item = tableWidget->item(1, 3);
    variant = item->data(Qt::DisplayRole);
    QVERIFY(item->flags() & Qt::ItemIsEditable);
    QCOMPARE(variant.toString(), QString("1.5"));

    item = tableWidget->item(1, 4);
    variant = item->data(Qt::DisplayRole);
    QVERIFY(item->flags() & Qt::ItemIsEditable);
    QCOMPARE(variant.toString(), QString("0"));

    item = tableWidget->item(1, 5);
    variant = item->data(Qt::DisplayRole);
    QVERIFY((item->flags() & Qt::ItemIsEditable) == false);
    QCOMPARE(variant.toDate(), QDate(2012,8,10));

    item = tableWidget->item(1, 6);
    variant = item->data(Qt::DisplayRole);
    QVERIFY((item->flags() & Qt::ItemIsEditable) == false);
    QCOMPARE(variant.toString(), QString("100.5"));

    item = tableWidget->item(1, 7);
    variant = item->data(Qt::DisplayRole);
    QVERIFY((item->flags() & Qt::ItemIsEditable) == false);
    QCOMPARE(variant.toString(), QString("Mitgliedsbeitrag"));
}

void AccountingEntryImporterViewTest::testBookBalance()
{
    membermanager::dao::BalanceDao balanceDao;
    QSqlTableModel *balanceTableModel = balanceDao.getModelByMemberId(1025);

    membermanager::gui::AccountingEntryImporterView accountingEntryImportView;
    QTableWidget *tableWidget = accountingEntryImportView.findChild<QTableWidget *>("tableWidget");


    QCOMPARE(balanceTableModel->rowCount(), 15);

    QPushButton *bookingButton = accountingEntryImportView.findChild<QPushButton *>("bookingButton");
    QTest::mouseClick(bookingButton, Qt::LeftButton);

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
}

} // namespace gui
} // namespace membermanagertest

QTEST_MAIN(membermanagertest::gui::AccountingEntryImporterViewTest)
#include "accountingentryimporterviewtest.moc"
