
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

    qaqbanking::swift::Transaction *transaction = new qaqbanking::swift::Transaction();
    transaction->setRemoteName("remoteName");
    transaction->setRemoteBankCode("0010011");
    transaction->setRemoteAccountNumber("1234567890");
    transaction->setValue(100.1);
    transaction->setValutaDate(QDate(2012, 10, 19));
    transaction->setDate(QDate(2012, 10, 22));
    transaction->setPurpose("PurposeText");
    transaction->setTransactionText("Transaction Text");
    transaction->setPrimanota("abc123");

    QList<qaqbanking::swift::Transaction *> transactions;
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
