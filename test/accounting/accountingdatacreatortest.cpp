
#include <QtTest/QtTest>

#include <QDate>
#include <QSharedPointer>

#include <QSqlDatabase>
#include <QSqlError>

#include "QDjango.h"
#include "QDjangoQuerySet.h"

#include "testconfig.h"

#include "entity/member.h"
#include "entity/bankaccount.h"
#include "entity/sepaaccount.h"
#include "entity/contribution.h"
#include "entity/balance.h"

#include "accounting/memberaccountingdata.h"

#include "accounting/accountingdatacreator.h"

namespace test {
namespace accounting {

class AccountingDataCreatorTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testCreateAccountingData();
};

void AccountingDataCreatorTest::initTestCase()
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

    QDjango::registerModel<membermanager::entity::Contribution>();
    QDjango::registerModel<membermanager::entity::BankAccount>();
    QDjango::registerModel<membermanager::entity::SepaAccount>();
    QDjango::registerModel<membermanager::entity::Balance>();

    QDjango::dropTables();
    QDjango::createTables();

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

void AccountingDataCreatorTest::testCreateAccountingData()
{
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

    membermanager::accounting::AccountingDataCreator accountingCreator(QDate(2013,12,1), "purpose", "info", 100000);
    membermanager::accounting::MemberAccountingData* data = accountingCreator.create(member);

    QCOMPARE(data->purpose(), QString("purpose"));
    QCOMPARE(data->accountingInfo(), QString("info"));
    QCOMPARE(data->firstname(), QString("James T."));
    QCOMPARE(data->name(), QString("Kirk"));
    QCOMPARE(data->memberId(), QString("1"));
    QCOMPARE(data->canCharge(), true);
    QCOMPARE(data->sepaBic(), QString("DUSSDEDDXXX"));
    QCOMPARE(data->sepaIban(), QString("DE26312345670012345678"));
    QCOMPARE(data->sepaMandateDate(), QDate(2013,11,30));
    QCOMPARE(data->sepaSequenceState(), QString("FIRST"));
    QCOMPARE(data->fee(), 15.0);
    QCOMPARE(data->donation(), 10.0);
    QCOMPARE(data->additionalDonation(), 3.0);
    QCOMPARE(data->additionalFee(), 2.0);
    QCOMPARE(data->amortization(), 8.0);
    QCOMPARE(data->accountingReference(), QString("100001"));

    delete data;

    data = accountingCreator.create(member);
    delete member;
    delete data;
    QCOMPARE(accountingCreator.getAccountingReference(), 100002);
}

}
}

QTEST_MAIN(test::accounting::AccountingDataCreatorTest)
#include "moc_accountingdatacreatortest.cpp"
