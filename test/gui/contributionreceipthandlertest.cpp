
#include <QtTest/QtTest>
#include <QSignalSpy>

#include <QObject>
#include <QString>
#include <QDate>
#include <QByteArray>
#include <QHash>
#include <QModelIndex>
#include <QSqlTableModel>
#include <QIODevice>
#include <QFile>
#include <QTextStream>
#include <QFileInfo>

#include "QDjango.h"

#include "testconfig.h"

#include "entity/member.h"
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
    void testRemoveRow();
    void testSum();
    void testSaveReceipt();
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
    QDjango::registerModel<membermanager::entity::Member>();
    QDjango::registerModel<membermanager::entity::Balance>();

    QDjango::dropTables();
    QDjango::createTables();

    membermanager::entity::Member *member1 = new membermanager::entity::Member();
    member1->setMemberId(1);
    member1->setName("Kirk");
    member1->setFirstname("James T.");
    member1->setEmail("enterprise@startrek.com");
    member1->setEntryDate(QDate(2001,8,10));
    member1->setStreet("universe");
    member1->setCity("NCC");
    member1->setZipCode("1701");
    member1->setCollectionState(membermanager::entity::Member::CollectionState::notKnown);
    member1->setState(membermanager::entity::Member::State::active);
    member1->save();
    delete member1;

    membermanager::entity::Balance *balance = new membermanager::entity::Balance();
    balance->setMemberId(1);
    balance->setValue(110.0);
    balance->setValuta(QDate(2006,10,15));
    balance->setPurpose("foo bar");
    balance->setAccount(12);
    balance->save();
    delete balance;

    balance = new membermanager::entity::Balance();
    balance->setMemberId(1);
    balance->setValue(10.0);
    balance->setValuta(QDate(2006,11,15));
    balance->setPurpose("bar foo");
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
    QCOMPARE(balanceList.size(), 2);
    QCOMPARE(spy.count(), 1);
}

void ContributionReceiptHandlerTest::testRemoveRow()
{
    membermanager::gui::ContributionReceiptHandler handler;
    QSignalSpy spy(&handler, SIGNAL(balanceListChanged()));

    handler.createReceipt(1,2006);

    handler.removeRow(0);

    QList<QObject *> balanceList = handler.balanceList();
    QCOMPARE(balanceList.size(), 1);
    QCOMPARE(spy.count(), 2);
}

void ContributionReceiptHandlerTest::testSum()
{
    membermanager::gui::ContributionReceiptHandler handler;
    QSignalSpy spy(&handler, SIGNAL(sumChanged()));

    handler.createReceipt(1,2006);

    QCOMPARE(spy.count(), 1);
    QCOMPARE(handler.sum(), 120.0);
}

void ContributionReceiptHandlerTest::testSaveReceipt()
{
    QFile file("test.tex");
    QVERIFY(file.open(QIODevice::WriteOnly | QIODevice::Text));
    QTextStream stream(&file);
    stream << "Mustermann\n";
    file.close();

    QString path = "file:.";
    QString filename = "file:test.tex";

    membermanager::gui::ContributionReceiptHandler handler;

    handler.createReceipt(1,2006);

    handler.saveReceipt(1, path, filename, 2006);

    QFileInfo fileInfo("./Spendenquittung-2006-Kirk-James T..tex");
    QVERIFY(fileInfo.exists());
}

}
}

QTEST_MAIN(test::gui::ContributionReceiptHandlerTest)
#include "moc_contributionreceipthandlertest.cpp"

