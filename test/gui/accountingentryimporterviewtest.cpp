#include "accountingentryimporterviewtest.h"

#include "gui/accountingentryimporterview.h"

#include <QVariant>
#include <QComboBox>
#include <QHeaderView>
#include <QTableWidget>
#include <QTableWidgetItem>

#include "testconfig.h"
#include "database/databaseutil.h"

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
    QVERIFY(item->flags() & Qt::ItemIsEditable);
    QCOMPARE(variant.toString(), QString("0"));

    item = tableWidget->item(0, 1);
    variant = item->data(Qt::DisplayRole);
    QVERIFY(item->flags() & Qt::ItemIsEditable);
    QCOMPARE(variant.toString(), QString("ignore"));

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
    QVERIFY(item->flags() & Qt::ItemIsEditable);
    QCOMPARE(variant.toString(), QString("1000"));

    item = tableWidget->item(1, 1);
    variant = item->data(Qt::DisplayRole);
    QVERIFY(item->flags() & Qt::ItemIsEditable);
    QCOMPARE(variant.toString(), QString("James T. Kirk"));

    item = tableWidget->item(1, 2);
    variant = item->data(Qt::DisplayRole);
    QVERIFY(item->flags() & Qt::ItemIsEditable);
    QCOMPARE(variant.toString(), QString("15"));

    item = tableWidget->item(1, 3);
    variant = item->data(Qt::DisplayRole);
    QVERIFY(item->flags() & Qt::ItemIsEditable);
    QCOMPARE(variant.toString(), QString("10"));

    item = tableWidget->item(1, 4);
    variant = item->data(Qt::DisplayRole);
    QVERIFY(item->flags() & Qt::ItemIsEditable);
    QCOMPARE(variant.toString(), QString("5"));

    item = tableWidget->item(1, 5);
    variant = item->data(Qt::DisplayRole);
    QVERIFY((item->flags() & Qt::ItemIsEditable) == false);
    QCOMPARE(variant.toDate(), QDate(2012,8,10));

    item = tableWidget->item(1, 6);
    variant = item->data(Qt::DisplayRole);
    QVERIFY((item->flags() & Qt::ItemIsEditable) == false);
    QCOMPARE(variant.toString(), QString("30"));

    item = tableWidget->item(1, 7);
    variant = item->data(Qt::DisplayRole);
    QVERIFY((item->flags() & Qt::ItemIsEditable) == false);
    QCOMPARE(variant.toString(), QString("Mitgliedsbeitrag"));
}

} // namespace gui
} // namespace membermanagertest

QTEST_MAIN(membermanagertest::gui::AccountingEntryImporterViewTest)
#include "accountingentryimporterviewtest.moc"
