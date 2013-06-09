
#include <QtTest/QtTest>

#include <QColor>
#include <QBrush>
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
    void testWrongValueToHigh();
    void testWrongValueToLow();
};

void BalancePersisterTest::initTestCase()
{
    qttestutil::database::DatabaseUtil database(DATABASEDRIVER);
    database.open(DATABASE);
    database.read(SQLTESTFILE);
}

void BalancePersisterTest::testBook()
{
    QTableWidget *tableWidget = new QTableWidget();
    tableWidget->setColumnCount(10);

    tableWidget->insertRow(0);

    QTableWidgetItem *item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("0")));
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    tableWidget->setItem(0, 0, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("-")));
    tableWidget->setItem(0, 1, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("0")));
    tableWidget->setItem(0, 2, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("0")));
    tableWidget->setItem(0, 3, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("0")));
    tableWidget->setItem(0, 4, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QDate(2006,1,23)));
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    tableWidget->setItem(0, 5, item);

    item = new QTableWidgetItem();
    item->setData(Qt::UserRole, QVariant(1));
    item->setData(Qt::DisplayRole, QVariant(QString("34.9")));
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    tableWidget->setItem(0, 6, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("LASTSCHRIFT  KDNR 1234 RGN 987")));
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    tableWidget->setItem(0, 7, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("INTERNET GMBH")));
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    tableWidget->setItem(0, 8, item);

    item = new QTableWidgetItem();
    item->setFlags(Qt::ItemIsUserCheckable);
    item->setCheckState(Qt::Unchecked);
    tableWidget->setItem(0, 9, item);


    tableWidget->insertRow(1);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("1025")));
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    tableWidget->setItem(1, 0, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("Kirk")));
    tableWidget->setItem(1, 1, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("98")));
    tableWidget->setItem(1, 2, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("1.5")));
    tableWidget->setItem(1, 3, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("1")));
    tableWidget->setItem(1, 4, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QDate(2012,11,23)));
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    tableWidget->setItem(1, 5, item);

    item = new QTableWidgetItem();
    item->setData(Qt::UserRole, QVariant(6));
    item->setData(Qt::DisplayRole, QVariant(QString("100.5")));
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    tableWidget->setItem(1, 6, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("mein Mitgliedsbeitrag")));
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    tableWidget->setItem(1, 7, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("Kirk")));
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    tableWidget->setItem(1, 8, item);

    item = new QTableWidgetItem();
    item->setFlags(Qt::ItemIsUserCheckable);
    item->setCheckState(Qt::Unchecked);
    tableWidget->setItem(1, 9, item);

    membermanager::accounting::BalancePersister balancePersister(tableWidget);
    balancePersister.booking();

    QSqlTableModel cashModel;
    cashModel.setTable(membermanager::dao::CashTable::TABLENAME);
    cashModel.setFilter(QString("%1=%2")
                        .arg(membermanager::dao::CashTable::COLUMNNAME[membermanager::dao::CashTable::dorfmitglied_pkey])
                        .arg(1025));
    cashModel.select();
    QCOMPARE(cashModel.rowCount(), 1);
    QSqlRecord record = cashModel.record(0);
    QVERIFY(record.value(membermanager::dao::CashTable::erfasst).toBool());


    QSqlTableModel saldoModel;
    saldoModel.setTable(membermanager::dao::BalanceTable::TABLENAME);
    saldoModel.setFilter(QString("%1=%2")
                         .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::kasse_pkey])
                         .arg(6));
    saldoModel.select();
    QCOMPARE(saldoModel.rowCount(), 3);

    record = saldoModel.record(0);
    QCOMPARE(record.value(membermanager::dao::BalanceTable::dorfmitglied_pkey).toString(), QString("1025"));
    QCOMPARE(record.value(membermanager::dao::BalanceTable::betrag).toString(), QString("98"));
    QCOMPARE(record.value(membermanager::dao::BalanceTable::bezeichnung).toString(), QString("mein Mitgliedsbeitrag"));
    QCOMPARE(record.value(membermanager::dao::BalanceTable::datum).toString(), QString("2012-11-23"));
    QCOMPARE(record.value(membermanager::dao::BalanceTable::konten).toString(), QString("11"));
    QCOMPARE(record.value(membermanager::dao::BalanceTable::info).toString(), QString("Automatische Buchung"));

    record = saldoModel.record(1);
    QCOMPARE(record.value(membermanager::dao::BalanceTable::dorfmitglied_pkey).toString(), QString("1025"));
    QCOMPARE(record.value(membermanager::dao::BalanceTable::betrag).toString(), QString("1.5"));
    QCOMPARE(record.value(membermanager::dao::BalanceTable::bezeichnung).toString(), QString("mein Mitgliedsbeitrag"));
    QCOMPARE(record.value(membermanager::dao::BalanceTable::datum).toString(), QString("2012-11-23"));
    QCOMPARE(record.value(membermanager::dao::BalanceTable::konten).toString(), QString("12"));
    QCOMPARE(record.value(membermanager::dao::BalanceTable::info).toString(), QString("Automatische Buchung"));

    record = saldoModel.record(2);
    QCOMPARE(record.value(membermanager::dao::BalanceTable::dorfmitglied_pkey).toString(), QString("1025"));
    QCOMPARE(record.value(membermanager::dao::BalanceTable::betrag).toString(), QString("1"));
    QCOMPARE(record.value(membermanager::dao::BalanceTable::bezeichnung).toString(), QString("mein Mitgliedsbeitrag"));
    QCOMPARE(record.value(membermanager::dao::BalanceTable::datum).toString(), QString("2012-11-23"));
    QCOMPARE(record.value(membermanager::dao::BalanceTable::konten).toString(), QString("4"));
    QCOMPARE(record.value(membermanager::dao::BalanceTable::info).toString(), QString("Automatische Buchung"));


    balancePersister.booking();

    cashModel.select();
    QCOMPARE(cashModel.rowCount(), 1);
    record = cashModel.record(0);
    QVERIFY(record.value(membermanager::dao::CashTable::erfasst).toBool());

    saldoModel.select();
    QCOMPARE(saldoModel.rowCount(), 3);
}

void BalancePersisterTest::testWrongValueToLow()
{
    QTableWidget *tableWidget = new QTableWidget();
    tableWidget->setColumnCount(10);

    tableWidget->insertRow(0);

    QTableWidgetItem *item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("0")));
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    tableWidget->setItem(0, 0, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("-")));
    tableWidget->setItem(0, 1, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("0")));
    tableWidget->setItem(0, 2, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("0")));
    tableWidget->setItem(0, 3, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("0")));
    tableWidget->setItem(0, 4, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QDate(2006,1,23)));
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    tableWidget->setItem(0, 5, item);

    item = new QTableWidgetItem();
    item->setData(Qt::UserRole, QVariant(1));
    item->setData(Qt::DisplayRole, QVariant(QString("34.9")));
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    tableWidget->setItem(0, 6, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("LASTSCHRIFT  KDNR 1234 RGN 987")));
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    tableWidget->setItem(0, 7, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("INTERNET GMBH")));
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    tableWidget->setItem(0, 8, item);

    item = new QTableWidgetItem();
    item->setFlags(Qt::ItemIsUserCheckable);
    item->setCheckState(Qt::Unchecked);
    tableWidget->setItem(0, 9, item);


    tableWidget->insertRow(1);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("1030")));
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    tableWidget->setItem(1, 0, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("Scott")));
    tableWidget->setItem(1, 1, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("80")));
    tableWidget->setItem(1, 2, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("0")));
    tableWidget->setItem(1, 3, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("0")));
    tableWidget->setItem(1, 4, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QDate(2012,11,22)));
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    tableWidget->setItem(1, 5, item);

    item = new QTableWidgetItem();
    item->setData(Qt::UserRole, QVariant(5));
    item->setData(Qt::DisplayRole, QVariant(QString("81.5")));
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    tableWidget->setItem(1, 6, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("mein Mitgliedsbeitrag")));
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    tableWidget->setItem(1, 7, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("Scott")));
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    tableWidget->setItem(1, 8, item);

    item = new QTableWidgetItem();
    item->setFlags(Qt::ItemIsUserCheckable);
    item->setCheckState(Qt::Unchecked);
    tableWidget->setItem(1, 9, item);

    membermanager::accounting::BalancePersister balancePersister(tableWidget);
    balancePersister.booking();

    QSqlTableModel cashModel;
    cashModel.setTable(membermanager::dao::CashTable::TABLENAME);
    cashModel.setFilter(QString("%1=%2")
                        .arg(membermanager::dao::CashTable::COLUMNNAME[membermanager::dao::CashTable::dorfmitglied_pkey])
                        .arg(1030));
    cashModel.select();
    QCOMPARE(cashModel.rowCount(), 0);
    QSqlRecord record = cashModel.record(0);
    QVERIFY(record.value(membermanager::dao::CashTable::erfasst).toBool() == false);


    QSqlTableModel saldoModel;
    saldoModel.setTable(membermanager::dao::BalanceTable::TABLENAME);
    saldoModel.setFilter(QString("%1=%2")
                         .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::kasse_pkey])
                         .arg(5));
    saldoModel.select();
    QCOMPARE(saldoModel.rowCount(), 0);

    item = tableWidget->item(1, 6);
    QBrush brush = item->background();
    QCOMPARE(brush.color().name(), QString("#ff0000"));
}

void BalancePersisterTest::testWrongValueToHigh()
{
    QTableWidget *tableWidget = new QTableWidget();
    tableWidget->setColumnCount(10);

    tableWidget->insertRow(0);

    QTableWidgetItem *item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("0")));
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    tableWidget->setItem(0, 0, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("-")));
    tableWidget->setItem(0, 1, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("0")));
    tableWidget->setItem(0, 2, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("0")));
    tableWidget->setItem(0, 3, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("0")));
    tableWidget->setItem(0, 4, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QDate(2006,1,23)));
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    tableWidget->setItem(0, 5, item);

    item = new QTableWidgetItem();
    item->setData(Qt::UserRole, QVariant(1));
    item->setData(Qt::DisplayRole, QVariant(QString("34.9")));
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    tableWidget->setItem(0, 6, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("LASTSCHRIFT  KDNR 1234 RGN 987")));
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    tableWidget->setItem(0, 7, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("INTERNET GMBH")));
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    tableWidget->setItem(0, 8, item);

    item = new QTableWidgetItem();
    item->setFlags(Qt::ItemIsUserCheckable);
    item->setCheckState(Qt::Unchecked);
    tableWidget->setItem(0, 9, item);


    tableWidget->insertRow(1);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("1030")));
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    tableWidget->setItem(1, 0, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("Scott")));
    tableWidget->setItem(1, 1, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("80")));
    tableWidget->setItem(1, 2, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("0")));
    tableWidget->setItem(1, 3, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("5")));
    tableWidget->setItem(1, 4, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QDate(2012,11,22)));
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    tableWidget->setItem(1, 5, item);

    item = new QTableWidgetItem();
    item->setData(Qt::UserRole, QVariant(7));
    item->setData(Qt::DisplayRole, QVariant(QString("81.5")));
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    tableWidget->setItem(1, 6, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("mein Mitgliedsbeitrag")));
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    tableWidget->setItem(1, 7, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("Scott")));
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    tableWidget->setItem(1, 8, item);

    item = new QTableWidgetItem();
    item->setFlags(Qt::ItemIsUserCheckable);
    item->setCheckState(Qt::Unchecked);
    tableWidget->setItem(1, 9, item);

    membermanager::accounting::BalancePersister balancePersister(tableWidget);
    balancePersister.booking();

    QSqlTableModel cashModel;
    cashModel.setTable(membermanager::dao::CashTable::TABLENAME);
    cashModel.setFilter(QString("%1=%2")
                        .arg(membermanager::dao::CashTable::COLUMNNAME[membermanager::dao::CashTable::dorfmitglied_pkey])
                        .arg(1030));
    cashModel.select();
    QCOMPARE(cashModel.rowCount(), 0);
    QSqlRecord record = cashModel.record(0);
    QVERIFY(record.value(membermanager::dao::CashTable::erfasst).toBool() == false);


    QSqlTableModel saldoModel;
    saldoModel.setTable(membermanager::dao::BalanceTable::TABLENAME);
    saldoModel.setFilter(QString("%1=%2")
                         .arg(membermanager::dao::BalanceTable::COLUMNNAME[membermanager::dao::BalanceTable::kasse_pkey])
                         .arg(5));
    saldoModel.select();
    QCOMPARE(saldoModel.rowCount(), 0);

    item = tableWidget->item(1, 6);
    QBrush brush = item->background();
    QCOMPARE(brush.color().name(), QString("#ff0000"));
}

} // namespace accounting
} // namespace membermanagertest


QTEST_MAIN(membermanagertest::accounting::BalancePersisterTest)
#include "moc_balancepersistertest.cpp"
