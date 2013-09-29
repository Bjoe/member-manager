
#include <QtTest/QtTest>

#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlError>

#include "QDjango.h"
#include "QDjangoWhere.h"
#include "QDjangoQuerySet.h"

#include "testconfig.h"

#include "entity/member.h"
#include "entity/contribution.h"
#include "entity/bankaccount.h"

#include "accounting/memberaccountingdata.h"

namespace test {
namespace accounting {

class MemberAccountingDataTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testCanCharge();
    void testDontCanCharge();
};

void MemberAccountingDataTest::initTestCase()
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

    QDjango::dropTables();
    QDjango::createTables();

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

void MemberAccountingDataTest::testCanCharge()
{
    membermanager::entity::Member member;
    member.setMemberId(1);
    member.setCollectionState(membermanager::entity::Member::CollectionState::known);
    membermanager::accounting::MemberAccountingData data(&member);

    QVERIFY(data.canCharge());
}

void MemberAccountingDataTest::testDontCanCharge()
{
    membermanager::entity::Member member;
    member.setMemberId(2);
    membermanager::accounting::MemberAccountingData data(&member);

    QVERIFY(data.canCharge() == false);
}

}
}

QTEST_MAIN(test::accounting::MemberAccountingDataTest)
#include "moc_memberaccountingdatatest.cpp"


