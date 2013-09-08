
#include <QtTest/QtTest>
#include <QObject>
#include <QString>
#include <QVariant>

#include "QDjango.h"

#include "testconfig.h"

#include "entity/bankaccount.h"

#include "dao/bankaccounttablemodel.h"

namespace test {
namespace dao {

class BankAccountTableModelTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testFindByMemberId();
};

void BankAccountTableModelTest::initTestCase()
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
    QDjango::registerModel<membermanager::entity::BankAccount>();

    QDjango::dropTables();
    QDjango::createTables();

    membermanager::entity::BankAccount *bankAccount = new membermanager::entity::BankAccount();
    bankAccount->setMemberId(1);
    bankAccount->setName("Sparstrumpf");
    bankAccount->setAccountNumber("123456");
    bankAccount->setCode("7654321");
    bankAccount->save();
    delete bankAccount;
}

void BankAccountTableModelTest::testFindByMemberId()
{
    membermanager::entity::BankAccount *bankAccount = membermanager::dao::BankAccountTableModel::findByMemberId(1);
    QCOMPARE(bankAccount->accountNumber(), QString("123456"));
}


}
}

QTEST_MAIN(test::dao::BankAccountTableModelTest)
#include "moc_bankaccounttablemodeltest.cpp"
