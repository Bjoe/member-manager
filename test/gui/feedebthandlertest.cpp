
#include <QtTest/QtTest>
#include <QSignalSpy>

#include <QList>
#include <QDate>

#include <QSqlError>
#include <QSqlDatabase>

#include <QClipboard>
#include <QApplication>

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
    void testCopyClipboard();
    void testCopyAllToClipboard();
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

    membermanager::entity::Balance* balance = new membermanager::entity::Balance();
    balance->setMemberId("1");
    balance->setValue(-15.0);
    balance->setAccount(-11);
    balance->setPurpose("Beitrag");
    balance->setValuta(QDate(2006,10,15));
    balance->save();
    delete balance;

    balance = new membermanager::entity::Balance();
    balance->setMemberId("1");
    balance->setValue(-10.0);
    balance->setAccount(-12);
    balance->setPurpose("Beitrag");
    balance->setValuta(QDate(2006,10,15));
    balance->save();
    delete balance;

    balance = new membermanager::entity::Balance();
    balance->setMemberId("1");
    balance->setValue(-3.0);
    balance->setAccount(-4);
    balance->setPurpose("Beitrag");
    balance->setValuta(QDate(2006,10,15));
    balance->save();
    delete balance;

    balance = new membermanager::entity::Balance();
    balance->setMemberId("1");
    balance->setValue(-2.0);
    balance->setAccount(-3);
    balance->setPurpose("Beitrag");
    balance->setValuta(QDate(2006,10,15));
    balance->save();
    delete balance;

    balance = new membermanager::entity::Balance();
    balance->setMemberId("1");
    balance->setValue(-5.0);
    balance->setAccount(-2);
    balance->setPurpose("Beitrag");
    balance->setValuta(QDate(2006,10,15));
    balance->save();
    delete balance;

    membermanager::entity::Member *member1 = new membermanager::entity::Member();
    member1->setMemberId("1");
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

    handler->calculate();

    QCOMPARE(spy.count(), 2);

    QList<QObject *> debtModel = handler->debtModel();
    QCOMPARE(debtModel.size(), 1);
}

void FeeDebtHandlerTest::testCalculateSignals()
{
    membermanager::gui::FeeDebtHandler *handler = new membermanager::gui::FeeDebtHandler(this);
    QSignalSpy progressSignal(handler, SIGNAL(progress(double)));
    QSignalSpy messageSignal(handler, SIGNAL(statusMessage(QString)));

    handler->calculate();

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

void FeeDebtHandlerTest::testCopyClipboard()
{
    QSettings settings;
    settings.setValue("main/name", QString("foobar e.V."));
    settings.setValue("sepa/iban", QString("DE26300501100021057476"));
    settings.setValue("sepa/bic", QString("DUSSDEDDXXX"));

    membermanager::gui::FeeDebtHandler *handler = new membermanager::gui::FeeDebtHandler(this);
    handler->calculate();

    handler->copyToClipboard(0);

    QClipboard *clipboard = QApplication::clipboard();
    QCOMPARE(clipboard->text(), QString("To: enterprise@startrek.com\n"
                                        "Subject: Chaosdorf Mitgliedsbeitrag Kontostand\n"
                                        "\n"
                                        "Hallo James T.,\n"
                                        "\n"
                                        "leider weist dein Mitgliedskontostand ein Sollwert von -25,00 EUR auf.\n"
                                        "Bitte zahle uns den ausstehenden Beitrag von 25,00 EUR auf\n"
                                        "folgendes Vereins Konto ein:\n"
                                        "Name: foobar e.V.\n"
                                        "IBAN: DE26300501100021057476\n"
                                        "BIC: DUSSDEDDXXX\n"
                                        "\n"
                                        "Als Referenz/MandateId bitte folgendes Eintragen:\n"
                                        "1\n"
                                        "\n"
                                        "Sollte es Probleme oder Fragen geben, dann wende dich bitte\n"
                                        "schnellstmoeglich an den Chaosdorf Vorstand\n"
                                        "Chaosdorf Vorstand <vorstand@chaosdorf.de>\n"
                                        "\n"
                                        "Diese Email wurde automatisch generiert und verschickt\n"));
}

void FeeDebtHandlerTest::testCopyAllToClipboard()
{
    membermanager::gui::FeeDebtHandler *handler = new membermanager::gui::FeeDebtHandler(this);
    handler->calculate();

    handler->copyAllToClipboard();

    QClipboard *clipboard = QApplication::clipboard();
    QCOMPARE(clipboard->text(), QString("Rueckstand\tName\tVorname\tEmail\n"
                                        "-25,00 EUR\tKirk\tJames T.\tenterprise@startrek.com\n"));
}

}
}

QTEST_MAIN(test::gui::FeeDebtHandlerTest)
#include "moc_feedebthandlertest.cpp"
