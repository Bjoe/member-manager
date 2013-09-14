
#include <QtTest/QtTest>

#include <QList>

#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlError>

#include "QDjango.h"

#include "testconfig.h"

#include "swift/transaction.h"
#include "entity/cashaccount.h"
#include "accounting/cashimporter.h"

namespace test {
namespace accounting {

class CashImporterTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testImport();
};

void CashImporterTest::initTestCase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase(DATABASEDRIVER);
    db.setDatabaseName(DATABASE);
    if (!db.open()) {
        QSqlError err = db.lastError();
        if (err.type() != QSqlError::NoError) {
            qWarning() << err.text();
        }
    }
    QDjango::setDatabase(db);
    QDjango::registerModel<membermanager::entity::CashAccount>();

    QDjango::dropTables();
    QDjango::createTables();
}

void CashImporterTest::testImport()
{
    QSqlTableModel *model = new QSqlTableModel();
    model->setTable("cashaccount");
    model->select();

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
    transactions.append(transaction);

    QCOMPARE(model->rowCount(), 0);

    membermanager::accounting::CashImporter importer;
    importer.import(transactions);

    model->select();
    QCOMPARE(model->rowCount(), 2);
}

}
}

QTEST_MAIN(test::accounting::CashImporterTest)
#include "moc_cashimportertest.cpp"
