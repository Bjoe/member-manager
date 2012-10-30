
#include <QtTest/QtTest>

#include <QList>
#include <QSqlRecord>
#include <QSqlTableModel>
#include <QTableWidgetItem>
#include <QTableWidget>

#include "dao/cashaccountdao.h"

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
    void testReadTransaction();
    void testImportTransaction();
};

void CashAccountDaoTest::initTestCase()
{
    qttestutil::database::DatabaseUtil database(DATABASEDRIVER);
    database.open(DATABASE);
    database.read(SQLTESTFILE);
}

void CashAccountDaoTest::testReadTransaction()
{
    QTableWidget *tableWidget = new QTableWidget();
    tableWidget->setColumnCount(9);

    membermanager::dao::CashAccountDao dao;
    dao.addTransaction(tableWidget);

    QCOMPARE(tableWidget->rowCount(), 3);

    QTableWidgetItem *item = tableWidget->item(0, 5);
    QVariant variant = item->data(Qt::DisplayRole);
    QVERIFY((item->flags() & Qt::ItemIsEditable) == false);
    QCOMPARE(variant.toDate(), QDate(2006,1,23));

    item = tableWidget->item(0, 6);
    variant = item->data(Qt::DisplayRole);
    QVERIFY((item->flags() & Qt::ItemIsEditable) == false);
    QCOMPARE(variant.toString(), QString("34.9"));

    item = tableWidget->item(0, 7);
    variant = item->data(Qt::DisplayRole);
    QVERIFY((item->flags() & Qt::ItemIsEditable) == false);
    QCOMPARE(variant.toString(), QString("LASTSCHRIFT  KDNR 1234 RGN 987"));

    item = tableWidget->item(0, 8);
    QVERIFY((item->flags() & Qt::ItemIsEditable) == false);
    QVERIFY(item->checkState() == Qt::Unchecked);
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

    GWEN_TIME *valutaTime = GWEN_Time_new(2012, 10, 19, 10, 30, 0, 0);
    AB_Transaction_SetValutaDate(abTransaction, valutaTime);

    GWEN_TIME *time = GWEN_Time_new(2012, 10, 22, 0, 5, 30, 0);
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
    model->setTable(membermanager::dao::KassaTable::TABLENAME);
    model->select();
    QCOMPARE(model->rowCount(), 4);

    membermanager::dao::CashAccountDao dao;
    dao.importTransactions(transactions);

    model->select();
    QCOMPARE(model->rowCount(), 5);

    model->setFilter(membermanager::dao::KassaTable::COLUMNNAME[membermanager::dao::KassaTable::bezeichnung] + "='PurposeText'");
    model->select();
    QCOMPARE(model->rowCount(), 1);

    QSqlRecord record = model->record(0);
    QCOMPARE(record.value(membermanager::dao::KassaTable::fremdname).toString(), QString("remoteName"));
    QCOMPARE(record.value(membermanager::dao::KassaTable::fremdblz).toString(), QString("80070011"));
    QCOMPARE(record.value(membermanager::dao::KassaTable::fremdktnr).toString(), QString("1234567890"));
    QCOMPARE(record.value(membermanager::dao::KassaTable::valutadatum).toString(), QString("2012-11-19T10:30:00"));
    QCOMPARE(record.value(membermanager::dao::KassaTable::buchungsdatum).toString(), QString("2012-11-22T00:05:30"));
    QCOMPARE(record.value(membermanager::dao::KassaTable::betrag).toString(), QString("100.1"));
    QCOMPARE(record.value(membermanager::dao::KassaTable::buschl).toString(), QString("Transaction Text"));
    QCOMPARE(record.value(membermanager::dao::KassaTable::bankbuschl).toString(), QString("23"));
    QCOMPARE(record.value(membermanager::dao::KassaTable::einleseid).toString(), QString("abc123"));
    QCOMPARE(record.value(membermanager::dao::KassaTable::bezeichnung).toString(), QString("PurposeText"));
    QCOMPARE(record.value(membermanager::dao::KassaTable::deleted).toString(), QString("false"));
    QCOMPARE(record.value(membermanager::dao::KassaTable::erfasst).toString(), QString("false"));
}

} // namespace accounting
} // namespace membermanagertest


QTEST_MAIN(membermanagertest::dao::CashAccountDaoTest)
#include "moc_cashaccountdaotest.cxx"
