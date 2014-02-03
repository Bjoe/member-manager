
#include <QtTest/QtTest>
#include <QSignalSpy>

#include <QObject>
#include <QChar>
#include <QString>
#include <QDate>
#include <QVariant>
#include <QSqlTableModel>

#include "QDjango.h"

#include "testconfig.h"

#include "entity/cashaccount.h"

#include "gui/cashimporthandler.h"

namespace test {
namespace gui {

class CashImportHandlerTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testCashProxyModelChanged();
    void testSelectYear();
    void testCashSelected();
};

void CashImportHandlerTest::initTestCase()
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
    cashAccount->setState("imported");
    cashAccount->setDate(QDate::currentDate());
    cashAccount->setMemberId("1");
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

    cashAccount = new membermanager::entity::CashAccount();
    cashAccount->setState("imported");
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
}

void CashImportHandlerTest::testCashProxyModelChanged()
{
    membermanager::gui::CashImportHandler *importHandler = new membermanager::gui::CashImportHandler(this);

    membermanager::gui::ProxyTableModel* proxyModel = importHandler->cashProxyModel();

    QCOMPARE(proxyModel->rowCount(), 1);

    importHandler->refresh();

    proxyModel = importHandler->cashProxyModel();
    QCOMPARE(proxyModel->rowCount(), 1);
}

void CashImportHandlerTest::testSelectYear()
{
    membermanager::gui::CashImportHandler *importHandler = new membermanager::gui::CashImportHandler(this);

    importHandler->selectYear(2010);

    membermanager::gui::ProxyTableModel* proxyModel = importHandler->cashProxyModel();
    QCOMPARE(proxyModel->rowCount(), 1);
}

void CashImportHandlerTest::testCashSelected()
{
    membermanager::gui::CashImportHandler* handler = new membermanager::gui::CashImportHandler(this);
    QSignalSpy spy(handler, SIGNAL(cashAccountChanged()));

    handler->selectedRow(0);

    QCOMPARE(spy.count(), 1);

    membermanager::entity::CashAccount* cashAccount = handler->cashAccount();
    QCOMPARE(cashAccount->remoteBankCode(), QString("7654321"));
}

}
}

QTEST_MAIN(test::gui::CashImportHandlerTest)
#include "moc_cashimporthandlertest.cpp"
