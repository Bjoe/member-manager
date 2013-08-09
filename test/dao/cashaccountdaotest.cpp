
#include <QtTest/QtTest>

#include <QList>
#include <QSqlRecord>
#include <QSqlTableModel>
#include <QTableWidgetItem>
#include <QTableWidget>

#include "dao/cashaccountdao.h"

#include "accounting/statemententry.h"

#include "testconfig.h"
#include "testcoverageobject.h"
#include "database/databaseutil.h"
#include "dao/databasestructure.h"

#include "swift/transaction.h"
#include "aqbanking/transaction.h"
#include "gwenhywfar/stringlist.h"

namespace membermanagertest
{
namespace dao
{

class CashAccountDaoTest : public qttestutil::TestCoverageObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testSaveRecord();
    void testReadRecord();
    void testUpdateRecord();
    void testReadTransaction();
    void testImportTransaction();
};

void CashAccountDaoTest::initTestCase()
{
    qttestutil::database::DatabaseUtil database(DATABASEDRIVER);
    database.open(DATABASE);
    database.read(SQLTESTFILE);
}

void CashAccountDaoTest::testUpdateRecord()
{
    membermanager::dao::CashAccountDao dao;
    membermanager::accounting::StatementEntry entry = dao.findById(2);

    entry.setValue(9999.99);

    QVERIFY(dao.updateRecord(entry));

    QSqlTableModel model;
    model.setTable(membermanager::dao::CashTable::TABLENAME);
    model.setFilter(QString("%1=%2")
                    .arg(membermanager::dao::CashTable::COLUMNNAME[membermanager::dao::CashTable::kasse_pkey])
                    .arg(2));
    model.select();

    QSqlRecord record = model.record(0);
    QCOMPARE(record.value(membermanager::dao::CashTable::betrag).toString(), QString("9999.99"));
}

void CashAccountDaoTest::testSaveRecord()
{
    membermanager::accounting::StatementEntry entry(9);
    entry.setRemoteName("PETER MUSTERMANN");
    entry.setRemoteAccountNumber("99994444");
    entry.setPurpose("test insert");
    entry.setTransactionText("action");

    membermanager::dao::CashAccountDao dao;
    QVERIFY(dao.saveRecord(entry));

    QSqlTableModel model;
    model.setTable(membermanager::dao::CashTable::TABLENAME);
    model.setFilter(QString("%1=%2")
                    .arg(membermanager::dao::CashTable::COLUMNNAME[membermanager::dao::CashTable::kasse_pkey])
                    .arg(9));
    model.select();

    QCOMPARE(model.rowCount(), 1);

    QSqlRecord record = model.record(0);
    QCOMPARE(record.value(membermanager::dao::CashTable::fremdname).toString(), QString("PETER MUSTERMANN"));
    QCOMPARE(record.value(membermanager::dao::CashTable::fremdktnr).toString(), QString("99994444"));
    QCOMPARE(record.value(membermanager::dao::CashTable::bezeichnung).toString(), QString("test insert"));
    QCOMPARE(record.value(membermanager::dao::CashTable::buschl).toString(), QString("action"));
}

void CashAccountDaoTest::testReadRecord()
{
    membermanager::dao::CashAccountDao dao;
    membermanager::accounting::StatementEntry entry = dao.findById(8);

    QCOMPARE(entry.getMemberId(), 1033);
    QCOMPARE(entry.getRemoteName(), QString("McCoy"));
    double expected = 81.5;
    double value = entry.getValue();
    QCOMPARE(value, expected);
}

void CashAccountDaoTest::testReadTransaction()
{
    QTableWidget *tableWidget = new QTableWidget();
    tableWidget->setColumnCount(10);

    membermanager::dao::CashAccountDao dao;
    dao.clearAndAddTransaction(tableWidget);

    QCOMPARE(tableWidget->rowCount(), 8);

    QTableWidgetItem *item = tableWidget->item(0, 0);
    QVariant variant = item->data(Qt::DisplayRole);
    QVERIFY((item->flags() & Qt::ItemIsEditable) == false);
    QCOMPARE(variant.toString(), QString(""));

    item = tableWidget->item(0, 1);
    variant = item->data(Qt::DisplayRole);
    QVERIFY(item->flags() & Qt::ItemIsEditable);
    QCOMPARE(variant.toString(), QString("-"));

    item = tableWidget->item(0, 2);
    variant = item->data(Qt::DisplayRole);
    QVERIFY(item->flags() & Qt::ItemIsEditable);
    QCOMPARE(variant.toString(), QString(""));

    item = tableWidget->item(0, 3);
    variant = item->data(Qt::DisplayRole);
    QVERIFY(item->flags() & Qt::ItemIsEditable);
    QCOMPARE(variant.toString(), QString(""));

    item = tableWidget->item(0, 4);
    variant = item->data(Qt::DisplayRole);
    QVERIFY(item->flags() & Qt::ItemIsEditable);
    QCOMPARE(variant.toString(), QString(""));

    item = tableWidget->item(0, 5);
    variant = item->data(Qt::DisplayRole);
    QVERIFY((item->flags() & Qt::ItemIsEditable) == false);
    QCOMPARE(variant.toDate(), QDate(2006,1,23));

    item = tableWidget->item(0, 6);
    variant = item->data(Qt::DisplayRole);
    QVERIFY((item->flags() & Qt::ItemIsEditable) == false);
    QCOMPARE(variant.toString(), QString("34.9"));
    variant = item->data(Qt::UserRole);
    QCOMPARE(variant.toInt(), 1);

    item = tableWidget->item(0, 7);
    variant = item->data(Qt::DisplayRole);
    QVERIFY((item->flags() & Qt::ItemIsEditable) == false);
    QCOMPARE(variant.toString(), QString("LASTSCHRIFT  KDNR 1234 RGN 987"));

    item = tableWidget->item(0, 8);
    variant = item->data(Qt::DisplayRole);
    QVERIFY((item->flags() & Qt::ItemIsEditable) == false);
    QCOMPARE(variant.toString(), QString("INTERNET GMBH"));

    item = tableWidget->item(0, 9);
    QVERIFY((item->flags() & Qt::ItemIsEditable) == false);
    QVERIFY(item->checkState() == Qt::Unchecked);






    item = tableWidget->item(2, 0);
    variant = item->data(Qt::DisplayRole);
    QVERIFY((item->flags() & Qt::ItemIsEditable) == false);
    QCOMPARE(variant.toString(), QString(""));

    item = tableWidget->item(2, 1);
    variant = item->data(Qt::DisplayRole);
    QVERIFY((item->flags() & Qt::ItemIsEditable) == false);
    QCOMPARE(variant.toString(), QString(""));

    item = tableWidget->item(2, 2);
    variant = item->data(Qt::DisplayRole);
    QVERIFY((item->flags() & Qt::ItemIsEditable) == false);
    QCOMPARE(variant.toString(), QString(""));

    item = tableWidget->item(2, 3);
    variant = item->data(Qt::DisplayRole);
    QVERIFY((item->flags() & Qt::ItemIsEditable) == false);
    QCOMPARE(variant.toString(), QString(""));

    item = tableWidget->item(2, 4);
    variant = item->data(Qt::DisplayRole);
    QVERIFY((item->flags() & Qt::ItemIsEditable) == false);
    QCOMPARE(variant.toString(), QString(""));

    item = tableWidget->item(2, 5);
    variant = item->data(Qt::DisplayRole);
    QVERIFY((item->flags() & Qt::ItemIsEditable) == false);
    QCOMPARE(variant.toDate(), QDate(2006,1,31));

    item = tableWidget->item(2, 6);
    variant = item->data(Qt::DisplayRole);
    QVERIFY((item->flags() & Qt::ItemIsEditable) == false);
    QCOMPARE(variant.toString(), QString("4.74"));
    variant = item->data(Qt::UserRole);
    QCOMPARE(variant.toInt(), 4);

    item = tableWidget->item(2, 7);
    variant = item->data(Qt::DisplayRole);
    QVERIFY((item->flags() & Qt::ItemIsEditable) == false);
    QCOMPARE(variant.toString(), QString("ABSCHLUSS  Abrechnung 30.01.2006 siehe Anlage"));

    item = tableWidget->item(2, 8);
    variant = item->data(Qt::DisplayRole);
    QVERIFY((item->flags() & Qt::ItemIsEditable) == false);
    QCOMPARE(variant.toString(), QString("-"));

    item = tableWidget->item(2, 9);
    QVERIFY((item->flags() & Qt::ItemIsEditable) == false);
    QVERIFY(item->checkState() == Qt::Checked);






    item = tableWidget->item(6, 0);
    variant = item->data(Qt::DisplayRole);
    QVERIFY((item->flags() & Qt::ItemIsEditable) == false);
    QCOMPARE(variant.toString(), QString("1033"));

    item = tableWidget->item(6, 1);
    variant = item->data(Qt::DisplayRole);
    QVERIFY((item->flags() & Qt::ItemIsEditable) == false);
    QCOMPARE(variant.toString(), QString("Leonard H."));

    item = tableWidget->item(6, 2);
    variant = item->data(Qt::DisplayRole);
    QVERIFY((item->flags() & Qt::ItemIsEditable) == false);
    QCOMPARE(variant.toString(), QString(""));

    item = tableWidget->item(6, 3);
    variant = item->data(Qt::DisplayRole);
    QVERIFY((item->flags() & Qt::ItemIsEditable) == false);
    QCOMPARE(variant.toString(), QString(""));

    item = tableWidget->item(6, 4);
    variant = item->data(Qt::DisplayRole);
    QVERIFY((item->flags() & Qt::ItemIsEditable) == false);
    QCOMPARE(variant.toString(), QString(""));

    item = tableWidget->item(6, 5);
    variant = item->data(Qt::DisplayRole);
    QVERIFY((item->flags() & Qt::ItemIsEditable) == false);
    QCOMPARE(variant.toDate(), QDate(2012,11,22));

    item = tableWidget->item(6, 6);
    variant = item->data(Qt::DisplayRole);
    QVERIFY((item->flags() & Qt::ItemIsEditable) == false);
    QCOMPARE(variant.toString(), QString("81.5"));
    variant = item->data(Qt::UserRole);
    QCOMPARE(variant.toInt(), 8);

    item = tableWidget->item(6, 7);
    variant = item->data(Qt::DisplayRole);
    QVERIFY((item->flags() & Qt::ItemIsEditable) == false);
    QCOMPARE(variant.toString(), QString("Mitgliedsbeitrag"));

    item = tableWidget->item(6, 8);
    variant = item->data(Qt::DisplayRole);
    QVERIFY((item->flags() & Qt::ItemIsEditable) == false);
    QCOMPARE(variant.toString(), QString("McCoy"));

    item = tableWidget->item(6, 9);
    QVERIFY((item->flags() & Qt::ItemIsEditable) == false);
    QVERIFY(item->checkState() == Qt::Checked);
}

void CashAccountDaoTest::testImportTransaction()
{
    AB_TRANSACTION *abTransaction = AB_Transaction_new();

    GWEN_STRINGLIST *stringList = GWEN_StringList_new();
    GWEN_StringList_InsertString(stringList, "remoteName", 1, 1);
    AB_Transaction_SetRemoteName(abTransaction, stringList);
    AB_Transaction_SetRemoteBankCode(abTransaction, "80070011");
    AB_Transaction_SetRemoteAccountNumber(abTransaction, "1234567890");

    AB_VALUE *abValue = AB_Value_fromDouble(100.1);
    AB_Transaction_SetValue(abTransaction, abValue);

    GWEN_TIME *valutaTime = GWEN_Time_new(2012, 10, 19, 0, 0, 0, 1);
    AB_Transaction_SetValutaDate(abTransaction, valutaTime);

    GWEN_TIME *time = GWEN_Time_new(2012, 10, 22, 0, 0, 0, 1);
    AB_Transaction_SetDate(abTransaction, time);

    GWEN_STRINGLIST *purposeStringList = GWEN_StringList_new();
    GWEN_StringList_InsertString(purposeStringList, "PurposeText", 1, 1);
    AB_Transaction_SetPurpose(abTransaction, purposeStringList);
    AB_Transaction_SetTransactionText(abTransaction, "Transaction Text");
    AB_Transaction_SetTransactionCode(abTransaction, 23);
    AB_Transaction_SetPrimanota(abTransaction, "abc123");

    qiabanking::swift::Transaction *transaction = new qiabanking::swift::Transaction(abTransaction);

    QList<qiabanking::swift::Transaction *> transactions;
    transactions.append(transaction);

    QSqlTableModel *model = new QSqlTableModel();
    model->setTable(membermanager::dao::CashTable::TABLENAME);
    model->select();
    QCOMPARE(model->rowCount(), 9);

    membermanager::dao::CashAccountDao dao;
    dao.importTransactions(transactions);

    model->select();
    QCOMPARE(model->rowCount(), 10);

    model->setFilter(membermanager::dao::CashTable::COLUMNNAME[membermanager::dao::CashTable::bezeichnung] + "='PurposeText'");
    model->select();
    QCOMPARE(model->rowCount(), 1);

    QSqlRecord record = model->record(0);
    QCOMPARE(record.value(membermanager::dao::CashTable::fremdname).toString(), QString("remoteName"));
    QCOMPARE(record.value(membermanager::dao::CashTable::fremdblz).toString(), QString("80070011"));
    QCOMPARE(record.value(membermanager::dao::CashTable::fremdktnr).toString(), QString("1234567890"));
    QCOMPARE(record.value(membermanager::dao::CashTable::valutadatum).toString(), QString("2012-11-19"));
    QCOMPARE(record.value(membermanager::dao::CashTable::buchungsdatum).toString(), QString("2012-11-22"));
    QCOMPARE(record.value(membermanager::dao::CashTable::betrag).toString(), QString("100.1"));
    QCOMPARE(record.value(membermanager::dao::CashTable::buschl).toString(), QString("Transaction Text"));
    QCOMPARE(record.value(membermanager::dao::CashTable::bankbuschl).toString(), QString("23"));
    QCOMPARE(record.value(membermanager::dao::CashTable::einleseid).toString(), QString("abc123"));
    QCOMPARE(record.value(membermanager::dao::CashTable::bezeichnung).toString(), QString("PurposeText"));
    QVERIFY(record.value(membermanager::dao::CashTable::deleted).toBool() == false);
    QVERIFY(record.value(membermanager::dao::CashTable::erfasst).toBool() == false);
}

} // namespace accounting
} // namespace membermanagertest


QTEST_MAIN(membermanagertest::dao::CashAccountDaoTest)
#include "moc_cashaccountdaotest.cpp"
