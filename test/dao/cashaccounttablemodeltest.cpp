
#include <QtTest/QtTest>
#include <QObject>
#include <QString>
#include <QDate>
#include <QVariant>
#include <QSqlTableModel>

#include "QDjango.h"

#include "testconfig.h"

#include "entity/cashaccount.h"

#include "dao/cashaccounttablemodel.h"

namespace test {
namespace dao {

class CashAccountTableModelTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testGetModel();
    void testSelectYear();
    void testRowSelected();
};

void CashAccountTableModelTest::initTestCase()
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

    membermanager::entity::CashAccount *cashAccount = new membermanager::entity::CashAccount();
    cashAccount->setBooked(false);
    cashAccount->setDate(QDate(2010,1,1));
    cashAccount->setMemberId("1");
    cashAccount->setPrimanota("prima");
    cashAccount->setPurpose("Geld");
    cashAccount->setRemoteAccountNumber("1234567");
    cashAccount->setRemoteBankCode("7654321");
    cashAccount->setRemoteName("Spar Strumpf");
    cashAccount->setTransactionCode(5);
    cashAccount->setTransactionText("LASTSCHRIFT");
    cashAccount->setValue(100.9);
    cashAccount->setValuta(QDate(2010,1,1));
    cashAccount->save();
    delete cashAccount;

    cashAccount = new membermanager::entity::CashAccount();
    cashAccount->setBooked(false);
    cashAccount->setDate(QDate(2011,1,1));
    cashAccount->setMemberId("1");
    cashAccount->setPrimanota("prima");
    cashAccount->setPurpose("Geld");
    cashAccount->setRemoteAccountNumber("1234567");
    cashAccount->setRemoteBankCode("7654321");
    cashAccount->setRemoteName("Spar Strumpf");
    cashAccount->setTransactionCode(5);
    cashAccount->setTransactionText("LASTSCHRIFT");
    cashAccount->setValue(100.9);
    cashAccount->setValuta(QDate(2011,1,1));
    cashAccount->save();
    delete cashAccount;

    cashAccount = new membermanager::entity::CashAccount();
    cashAccount->setBooked(false);
    cashAccount->setDate(QDate(2011,1,1));
    cashAccount->setMemberId("1");
    cashAccount->setPrimanota("prima");
    cashAccount->setPurpose("Geld");
    cashAccount->setRemoteAccountNumber("1234567");
    cashAccount->setRemoteBankCode("7654321");
    cashAccount->setRemoteName("Spar Strumpf");
    cashAccount->setTransactionCode(5);
    cashAccount->setTransactionText("LASTSCHRIFT");
    cashAccount->setValue(100.9);
    cashAccount->setValuta(QDate(2011,1,1));
    cashAccount->save();
    delete cashAccount;
}

void CashAccountTableModelTest::testGetModel()
{
    QSqlTableModel* model = membermanager::dao::CashAccountTableModel::createModel(2010);
    QCOMPARE(model->rowCount(), 1);

    delete model;
}

void CashAccountTableModelTest::testSelectYear()
{
    QSqlTableModel* model = membermanager::dao::CashAccountTableModel::createModel(2010);
    membermanager::dao::CashAccountTableModel::selectYear(model, 2011);
    QCOMPARE(model->rowCount(), 2);

    delete model;
}

void CashAccountTableModelTest::testRowSelected()
{
    QSqlTableModel* model = membermanager::dao::CashAccountTableModel::createModel(2010);

    membermanager::entity::CashAccount *cashAcount = membermanager::dao::CashAccountTableModel::findBySelectedRow(model, 0);
    QCOMPARE(cashAcount->remoteBankCode(), QString("7654321"));

    delete cashAcount;
    delete model;
}

}
}

QTEST_MAIN(test::dao::CashAccountTableModelTest)
#include "moc_cashaccounttablemodeltest.cpp"
