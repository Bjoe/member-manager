
#include <QtTest/QtTest>
#include <QSignalSpy>

#include <QObject>
#include <QString>
#include <QDate>
#include <QByteArray>
#include <QHash>
#include <QModelIndex>
#include <QSqlTableModel>

#include "QDjango.h"

#include "testconfig.h"

#include "entity/balance.h"

#include "gui/contributionreceipthandler.h"

namespace test {
namespace gui {

class ContributionReceiptHandlerTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testCreateReceipt();
};

void ContributionReceiptHandlerTest::initTestCase()
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
    QDjango::registerModel<membermanager::entity::Balance>();

    QDjango::dropTables();
    QDjango::createTables();

    membermanager::entity::Balance *balance = new membermanager::entity::Balance();
    balance->setMemberId(1);
    balance->setValue(155.0);
    balance->setValuta(QDate(2006,10,15));
    balance->setPurpose("foo bar");
    balance->setAccount(12);
    balance->save();
    delete balance;
}

void ContributionReceiptHandlerTest::testCreateReceipt()
{
    membermanager::gui::ContributionReceiptHandler handler;
    QSignalSpy spy(&handler, SIGNAL(balanceListChanged()));

    handler.createReceipt(1,2006);

    QList<QObject *> balanceList = handler.balanceList();
    QCOMPARE(balanceList.size(), 1);
    QCOMPARE(spy.count(), 1);
}

}
}

QTEST_MAIN(test::gui::ContributionReceiptHandlerTest)
#include "moc_contributionreceipthandlertest.cpp"

