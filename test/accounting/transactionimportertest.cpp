
#include <QtTest/QtTest>

#include <QString>
#include <QVariant>
#include <QTableWidget>
#include <QTableWidgetItem>

#include "accounting/transactionimporter.h"

#include "testcoverageobject.h"
#include "testconfig.h"
#include "database/databaseutil.h"

namespace membermanagertest
{
namespace accounting
{

class TransactionImporterTest : public qttestutil::TestCoverageObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testImport();
};

void TransactionImporterTest::initTestCase()
{
    qttestutil::database::DatabaseUtil database(DATABASEDRIVER);
    database.open(DATABASE);
    database.read(SQLTESTFILE);
}

void TransactionImporterTest::testImport()
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

    membermanager::accounting::TransactionImporter transactionImporter;


    QTableWidget *tableWidget = accountingEntryTable;


    QCOMPARE(tableWidget->rowCount(), 2);

    item = tableWidget->item(0, 0);
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

} // namespace accounting
} // namespace membermanagertest


QTEST_MAIN(membermanagertest::accounting::TransactionImporterTest)
#include "moc_transactionimportertest.cxx"
