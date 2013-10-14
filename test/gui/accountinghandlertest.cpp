
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
    QDjango::registerModel<membermanager::entity::Balance>();

    QDjango::dropTables();
    QDjango::createTables();

    membermanager::entity::Member* member = new membermanager::entity::Member();
    member->setMemberId(1);
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
    bankAccount->setMemberId(1);
    bankAccount->setAccountNumber("22334455");
    bankAccount->setCode("80070099");
    bankAccount->setName("Strumpfspar");
    bankAccount->save();
    delete bankAccount;

    membermanager::entity::Contribution *contribution = new membermanager::entity::Contribution();
    contribution->setMemberId(1);
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

    membermanager::accounting::MemberAccountingData* accountingData = new membermanager::accounting::MemberAccountingData();
    accountingData->setAccountingInfo("foo");
    accountingData->setPurpose("bar");
    accountingData->setAdditionalDonation(3.0);
    accountingData->setAdditionalFee(2.0);
    accountingData->setAmortization(8.0);
    accountingData->setBankAccountNumber("22334455");
    accountingData->setBankCode("80070099");
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

    handler.book("testfile");

    QFile file("testfile.csv");
    QVERIFY(file.open(QIODevice::ReadOnly | QIODevice::Text));

    QTextStream stream(&file);
    QCOMPARE(stream.readLine(), QString("29.09.2013;Lastschrift Einzug 011;011 Mitgliedsbeitrag Kirk, James T.;15"));

    file.close();

    QFile file2("testfile.txt");
    QVERIFY(file2.open(QIODevice::ReadOnly | QIODevice::Text));

    QTextStream stream2(&file2);

    QString line = stream2.readLine();

    QRegExp regExp(".*BAR BEITRAG 15EUR SPENDE 101  0102EUR CCC 5EUR RATE 8EUR.*");
    QVERIFY(regExp.exactMatch(line));

    file2.close();

    QDjangoQuerySet<membermanager::entity::Balance> result;
    QCOMPARE(result.size(), 10);
    QList<QVariantMap> propertyMaps = result.values(QStringList() << "value" << "purpose");
    QVariantMap property = propertyMaps.at(0);
    QCOMPARE(property["value"], QVariant(-15.0));
    QCOMPARE(property["purpose"], QVariant("Mitgliedsbeitrag foo"));
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

    handler.book("testfile");

    QCOMPARE(messageSignal.count(), 2);
    QCOMPARE(progressSignal.count(), 2);

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

