#include <QtTest/QtTest>
#include "testcoverageobject.h"

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

class AccountingEntryImporterViewTest : public qttestutil::TestCoverageObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testImport();
};

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
    QCOMPARE(tableWidget->columnCount(), 9);
    QHeaderView *headerView = tableWidget->horizontalHeader();
    QCOMPARE(headerView->count(), 9);
    QCOMPARE(tableWidget->rowCount(), 0);
    QVERIFY(tableWidget->itemDelegateForColumn(1));

    QPushButton *importButton = accountingEntryImportView.findChild<QPushButton *>("importButton");
    QTest::mouseClick(importButton, Qt::LeftButton);

    QCOMPARE(tableWidget->rowCount(), 2);

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

    item = tableWidget->item(0, 8);
    QVERIFY((item->flags() & Qt::ItemIsEditable) == false);
    QVERIFY(item->checkState() == Qt::Unchecked);


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

    item = tableWidget->item(1, 8);
    QVERIFY((item->flags() & Qt::ItemIsEditable) == false);
    QVERIFY(item->checkState() == Qt::Unchecked);
}

} // namespace gui
} // namespace membermanagertest

QTEST_MAIN(membermanagertest::gui::AccountingEntryImporterViewTest)
#include "moc_accountingentryimporterviewtest.cxx"
