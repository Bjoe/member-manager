
#include <QtTest/QtTest>
#include <QSignalSpy>

#include <QString>
#include <QDate>

#include <QSqlDatabase>
#include <QSqlError>

#include "QDjango.h"
#include "QDjangoQuerySet.h"
#include "QDjangoWhere.h"

#include "testconfig.h"

#include "entity/cashaccount.h"
#include "entity/balance.h"

#include "gui/balancepersisthandler.h"

namespace test {
namespace gui {

class BalancePersistHandlerTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testPersist();
};

void BalancePersistHandlerTest::initTestCase()
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
    QDjango::registerModel<membermanager::entity::Balance>();

    QDjango::dropTables();
    QDjango::createTables();

    membermanager::entity::CashAccount *cashAccount = new membermanager::entity::CashAccount();
    cashAccount->setBooked(false);
    cashAccount->setDeleted(false);
    cashAccount->setDate(QDate::currentDate());
    cashAccount->setPrimanota("prima");
    cashAccount->setPurpose("Geld");
    cashAccount->setRemoteAccountNumber("1234567");
    cashAccount->setRemoteBankCode("7654321");
    cashAccount->setRemoteName("Spar Strumpf");
    cashAccount->setTransactionCode(5);
    cashAccount->setTransactionText("LASTSCHRIFT");
    cashAccount->setValue(100.9);
    cashAccount->setValuta(QDate::currentDate());
    cashAccount->save();
    delete cashAccount;
}

void BalancePersistHandlerTest::testPersist()
{
    QDjangoQuerySet<membermanager::entity::CashAccount> cashAccountSet;
    membermanager::entity::CashAccount *cashAccount = new membermanager::entity::CashAccount();
    cashAccountSet.at(0, cashAccount);

    membermanager::gui::BalancePersistHandler *handler = new membermanager::gui::BalancePersistHandler(this);

    handler->setCashAccount(cashAccount);
    handler->setMemberId("1023");
    handler->setFee("15");
    handler->setDonation("5");
    handler->setAdditional("10");
    handler->setTax("6");

    handler->onBooked();

    QDjangoQuerySet<membermanager::entity::CashAccount> actualCashAccountSet;
    QCOMPARE(actualCashAccountSet.count(), 1);

    membermanager::entity::CashAccount *actualCashAccount = new membermanager::entity::CashAccount();
    actualCashAccountSet.at(0, actualCashAccount);

    QCOMPARE(actualCashAccount->memberId(), 1023);

    QDjangoQuerySet<membermanager::entity::Balance> balanceSet;

    QCOMPARE(balanceSet.count(), 4);

    membermanager::entity::Balance *balance = new membermanager::entity::Balance();
    balanceSet.at(0, balance);

    QCOMPARE(balance->account(), 11);
}

}
}

QTEST_MAIN(test::gui::BalancePersistHandlerTest)
#include "moc_balancepersisthandlertest.cpp"
