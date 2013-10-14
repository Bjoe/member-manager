
#include <QtTest/QtTest>
#include <QSignalSpy>

#include <QList>
#include <QDate>

#include <QSqlError>
#include <QSqlDatabase>

#include "QDjango.h"

#include "testconfig.h"

#include "entity/member.h"
#include "entity/balance.h"

#include "accounting/memberdebt.h"

#include "gui/feedebthandler.h"

namespace test {
namespace gui {

class FeeDebtHandlerTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testCalculate();
    void testCalculateSignals();
};

void FeeDebtHandlerTest::initTestCase()
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
    QDjango::registerModel<membermanager::entity::Member>();

    QDjango::dropTables();
    QDjango::createTables();

    membermanager::entity::Balance *balance = new membermanager::entity::Balance();
    balance->setMemberId(1);
    balance->setValue(-15.0);
    balance->setAccount(-11);
    balance->setPurpose("Beitrag");
    balance->setValuta(QDate(2006,10,15));
    balance->save();
    delete balance;

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
}

void FeeDebtHandlerTest::testCalculate()
{
    membermanager::gui::FeeDebtHandler *handler = new membermanager::gui::FeeDebtHandler(this);
    QSignalSpy spy(handler, SIGNAL(debtModelChanged()));

    handler->onCalculate();

    QCOMPARE(spy.count(), 1);

    QList<QObject *> debtModel = handler->debtModel();
    QCOMPARE(debtModel.size(), 1);
}

void FeeDebtHandlerTest::testCalculateSignals()
{
    membermanager::gui::FeeDebtHandler *handler = new membermanager::gui::FeeDebtHandler(this);
    QSignalSpy progressSignal(handler, SIGNAL(progress(double)));
    QSignalSpy messageSignal(handler, SIGNAL(statusMessage(QString)));

    handler->onCalculate();

    QCOMPARE(messageSignal.count(), 2);
    QCOMPARE(progressSignal.count(), 2);

    QList<QVariant> messageArgument1 = messageSignal.takeFirst();
    QCOMPARE(messageArgument1.at(0).toString(), QString("Calculate in progress ... please wait"));

    QList<QVariant> messageArgument2 = messageSignal.takeLast();
    QCOMPARE(messageArgument2.at(0).toString(), QString("Calculate done"));

    QList<QVariant> progressArgument1 = progressSignal.takeFirst();
    QCOMPARE(progressArgument1.at(0).toDouble(), 0.0);

    QList<QVariant> progressArgument2 = progressSignal.takeLast();
    QCOMPARE(progressArgument2.at(0).toDouble(), 1.0);
}

}
}

QTEST_MAIN(test::gui::FeeDebtHandlerTest)
#include "moc_feedebthandlertest.cpp"
