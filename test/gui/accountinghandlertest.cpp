
#include <QtTest/QtTest>
#include <QSignalSpy>

#include <QSqlDatabase>
#include <QSqlError>

#include <QObject>
#include <QString>
#include <QList>
#include <QStringList>
#include <QVariant>
#include <QVariantMap>
#include <QFile>
#include <QTextStream>
#include <QRegExp>

#include <QSettings>

#include "QDjango.h"
#include "QDjangoQuerySet.h"

#include "testconfig.h"

#include "entity/member.h"
#include "entity/bankaccount.h"
#include "entity/sepaaccount.h"
#include "entity/contribution.h"
#include "entity/balance.h"

#include "accounting/memberaccountingdata.h"

#include "gui/accountinghandler.h"

namespace test {
namespace gui {

class AccountingHandlerTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testGetAccountingData();
    void testBook();
    void testBookSignals();
};

void AccountingHandlerTest::initTestCase()
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
    QDjango::registerModel<membermanager::entity::Contribution>();
    QDjango::registerModel<membermanager::entity::BankAccount>();
    QDjango::registerModel<membermanager::entity::SepaAccount>();
    QDjango::registerModel<membermanager::entity::Balance>();

    QDjango::dropTables();
    QDjango::createTables();

    membermanager::entity::Member* member = new membermanager::entity::Member();
    member->setMemberId("1");
    member->setName("Kirk");
    member->setFirstname("James T.");
    member->setEmail("enterprise@startrek.com");
    member->setEntryDate(QDate(2013,8,10));
    member->setStreet("universe");
    member->setCity("NCC");
    member->setZipCode("1701");
    member->setCollectionState(membermanager::entity::Member::CollectionState::known);
    member->setState(membermanager::entity::Member::State::active);
    member->save();
    delete member;

    membermanager::entity::BankAccount *bankAccount = new membermanager::entity::BankAccount();
    bankAccount->setMemberId("1");
    bankAccount->setAccountNumber("22334455");
    bankAccount->setCode("80070099");
    bankAccount->setName("Strumpfspar");
    bankAccount->save();
    delete bankAccount;

    membermanager::entity::SepaAccount *sepaAccount = new membermanager::entity::SepaAccount();
    sepaAccount->setMemberId("1");
    sepaAccount->setBic("DUSSDEDDXXX");
    sepaAccount->setIban("DE26312345670012345678");
    sepaAccount->setMandateDate(QDate(2013,11,30));
    sepaAccount->setSequenceState("FIRST");
    sepaAccount->save();
    delete sepaAccount;

    membermanager::entity::Contribution *contribution = new membermanager::entity::Contribution();
    contribution->setMemberId("1");
    contribution->setFee(15.0);
    contribution->setDonation(10.0);
    contribution->setAdditionalDonation(3.0);
    contribution->setAdditionalFee(2.0);
    contribution->setAmortization(8.0);
    contribution->setValidFrom(QDate(2013, 8, 1));
    contribution->save();
    delete contribution;

}

void AccountingHandlerTest::testGetAccountingData()
{
    membermanager::gui::AccountingHandler* handler = new membermanager::gui::AccountingHandler();
    QSignalSpy spy(handler, SIGNAL(accountingDataListChanged()));

    QCOMPARE(spy.count(), 0);
    QList<QObject *> list = handler->accountingDataList();
    QCOMPARE(list.size(), 0);

    handler->onRefresh();

    QCOMPARE(spy.count(), 1);
    list = handler->accountingDataList();
    QCOMPARE(list.size(), 1);


    handler->onRefresh();

    QCOMPARE(spy.count(), 2);
    list = handler->accountingDataList();
    QCOMPARE(list.size(), 1);

    delete handler;
}

void AccountingHandlerTest::testBook()
{
    QSettings settings;
    settings.setValue("bank/name", QString("foobar"));
    settings.setValue("bank/code", QString("39912399"));
    settings.setValue("bank/account", QString("123456"));

    settings.setValue("main/name", QString("foobar e.V."));
    settings.setValue("main/creditorId", QString("DE202300000782585"));
    settings.setValue("sepa/iban", QString("DE26300501100021057476"));
    settings.setValue("sepa/bic", QString("DUSSDEDDXXX"));

    membermanager::accounting::MemberAccountingData* accountingData = new membermanager::accounting::MemberAccountingData();
    accountingData->setAccountingInfo("foo");
    accountingData->setPurpose("bar");
    accountingData->setAdditionalDonation(3.0);
    accountingData->setAdditionalFee(2.0);
    accountingData->setAmortization(8.0);
    accountingData->setBankAccountNumber("22334455");
    accountingData->setBankCode("80070099");
    accountingData->setSepaBic("DUSSDEDDXXX");
    accountingData->setSepaIban("DE26312345670012345678");
    accountingData->setSepaMandateDate(QDate(2013,11,30));
    accountingData->setSepaSequenceState("FIRST");
    accountingData->setAccountingReference("9876543210");
    accountingData->setCollectionState(static_cast<char>(membermanager::entity::Member::CollectionState::known));
    accountingData->setDonation(10.0);
    accountingData->setFee(15.0);
    accountingData->setFirstname("James T.");
    accountingData->setMemberId("1");
    accountingData->setName("Kirk");
    accountingData->setValuta(QDate(2013, 9, 29));

    QList<QObject *> accountingList;
    accountingList.append(accountingData);


    membermanager::gui::AccountingHandler handler;

    handler.setAccountingDataList(accountingList);

    handler.book("file:testfile");

    QFile file("testfile.csv");
    QVERIFY(file.open(QIODevice::ReadOnly | QIODevice::Text));

    QTextStream stream(&file);
    QCOMPARE(stream.readLine(), QString("29.09.2013;Lastschrift Einzug 011;011 Mitgliedsbeitrag 9876543210 1 James T., Kirk;15"));

    file.close();

    QFile file2("testfile.txt");
    QVERIFY(file2.open(QIODevice::ReadOnly | QIODevice::Text));

    QTextStream stream2(&file2);

    QString line = stream2.readLine();

    QRegExp regExp(".*BAR.*");
    QVERIFY(regExp.exactMatch(line));

    file2.close();

    QFile sepaFile("testfile-FIRST.xml");
    QVERIFY(sepaFile.open(QIODevice::ReadOnly | QIODevice::Text));

    QTextStream sepaStream(&sepaFile);

    QString sepaContent = sepaStream.readAll();

    regExp.setPattern(".*bar.*");
    QVERIFY(regExp.exactMatch(sepaContent));

    regExp.setPattern(".*9876543210.*");
    QVERIFY(regExp.exactMatch(sepaContent));

    sepaFile.close();

    QDjangoQuerySet<membermanager::entity::SepaAccount> accountResult;
    QList<QVariantMap> propertyMaps = accountResult.values(QStringList() << "sequenceState");
    QVariantMap property = propertyMaps.at(0);
    // TODO QCOMPARE(property["sequenceState"], QVariant("FOLLOWING"));

    QDjangoQuerySet<membermanager::entity::Balance> result;
    QCOMPARE(result.size(), 9);
    propertyMaps = result.values(QStringList() << "value" << "purpose" << "accountingReference");
    property = propertyMaps.at(0);
    QCOMPARE(property["value"], QVariant(-15.0));
    QCOMPARE(property["purpose"], QVariant("Mitgliedsbeitrag foo"));
    QCOMPARE(property["accountingReference"], QVariant("9876543210"));
}

void AccountingHandlerTest::testBookSignals()
{
    membermanager::accounting::MemberAccountingData* accountingData = new membermanager::accounting::MemberAccountingData();
    accountingData->setAccountingInfo("foo");
    accountingData->setPurpose("bar");
    accountingData->setAdditionalDonation(3.0);
    accountingData->setAdditionalFee(2.0);
    accountingData->setAmortization(8.0);
    accountingData->setBankAccountNumber("22334455");
    accountingData->setBankCode("80070099");
    accountingData->setSepaBic("DUSSDEDDXXX");
    accountingData->setSepaIban("DE26312345670012345678");
    accountingData->setSepaMandateDate(QDate(2013,11,30));
    accountingData->setSepaSequenceState("FIRST");
    accountingData->setCollectionState(static_cast<char>(membermanager::entity::Member::CollectionState::known));
    accountingData->setDonation(10.0);
    accountingData->setFee(15.0);
    accountingData->setFirstname("James T.");
    accountingData->setMemberId("1");
    accountingData->setName("Kirk");
    accountingData->setValuta(QDate(2013, 9, 29));

    QList<QObject *> accountingList;
    accountingList.append(accountingData);


    membermanager::gui::AccountingHandler handler;
    QSignalSpy progressSignal(&handler, SIGNAL(progress(double)));
    QSignalSpy messageSignal(&handler, SIGNAL(statusMessage(QString)));

    handler.setAccountingDataList(accountingList);

    handler.book("file:testfile");

    QCOMPARE(messageSignal.count(), 4);
    QCOMPARE(progressSignal.count(), 3);

    QList<QVariant> messageArgument1 = messageSignal.takeFirst();
    QCOMPARE(messageArgument1.at(0).toString(), QString("Booking in progess ... please wait"));

    QList<QVariant> messageArgument2 = messageSignal.takeLast();
    QCOMPARE(messageArgument2.at(0).toString(), QString("Booking done"));

    QList<QVariant> progressArgument1 = progressSignal.takeFirst();
    QCOMPARE(progressArgument1.at(0).toDouble(), 0.0);

    QList<QVariant> progressArgument2 = progressSignal.takeLast();
    QCOMPARE(progressArgument2.at(0).toDouble(), 1.0);
}

}
}

QTEST_MAIN(test::gui::AccountingHandlerTest)
#include "moc_accountinghandlertest.cpp"

