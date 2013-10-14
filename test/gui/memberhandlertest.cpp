
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

#include "entity/member.h"
#include "entity/contribution.h"
#include "entity/bankaccount.h"
#include "entity/balance.h"

#include "gui/memberhandler.h"
#include "gui/proxytablemodel.h"

namespace test {
namespace gui {

class MemberHandlerTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testContribuitonProxyModelChanged();
    void testBalanceProxyModelChanged();
    void testMemberSelected();
    void testNewMember();
    void testNewContribution();
};

void MemberHandlerTest::initTestCase()
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

    membermanager::entity::Member *member = new membermanager::entity::Member();
    member->setMemberId(1);
    member->setName("Kirk");
    member->setFirstname("James T.");
    member->setEmail("enterprise@startrek.com");
    member->setEntryDate(QDate(2013,8,10));
    member->setStreet("universe");
    member->setCity("NCC");
    member->setZipCode("1701");
    member->setCollectionState(membermanager::entity::Member::CollectionState::known);
    member->setState(membermanager::entity::Member::State::deleted);
    member->save();
    delete member;

    membermanager::entity::BankAccount *bankAccount = new membermanager::entity::BankAccount();
    bankAccount->setMemberId(2);
    bankAccount->setAccountNumber("123456");
    bankAccount->setName("Sparstrumpf");
    bankAccount->setCode("7654321");
    bankAccount->save();
    delete bankAccount;

    membermanager::entity::Contribution *contribution = new membermanager::entity::Contribution();
    contribution->setMemberId(2);
    contribution->setFee(15.0);
    contribution->setAdditionalFee(0);
    contribution->setDonation(0);
    contribution->setValidFrom(QDate::currentDate());
    contribution->save();
    delete contribution;

    membermanager::entity::Balance *balance = new membermanager::entity::Balance();
    balance->setMemberId(2);
    balance->setValue(155.0);
    balance->setValuta(QDate::currentDate());
    balance->setPurpose("foo bar");
    balance->setAccount(23);
    balance->save();
    delete balance;

    member = new membermanager::entity::Member();
    member->setMemberId(2);
    member->setName("McCoy");
    member->setFirstname("Dr. Leonard");
    member->setNickname("Pille");
    member->setEmail("arzt@startrek.com");
    member->setEntryDate(QDate(2013,9,1));
    member->setStreet("universe");
    member->setCity("NCC");
    member->setZipCode("1701");
    member->setCollectionState(membermanager::entity::Member::CollectionState::notKnown);
    member->setState(membermanager::entity::Member::State::active);
    member->save();
    delete member;
}

void MemberHandlerTest::testContribuitonProxyModelChanged()
{
    membermanager::gui::MemberHandler *handler = new membermanager::gui::MemberHandler(this);
    QSignalSpy spy(handler, SIGNAL(memberChanged()));

    handler->onSelectedMemberId(2);
    membermanager::gui::ProxyTableModel *model = handler->contributionProxyModel();
    QCOMPARE(model->rowCount(), 1);
    QCOMPARE(spy.count(), 1);
}

void MemberHandlerTest::testBalanceProxyModelChanged()
{
    membermanager::gui::MemberHandler *handler = new membermanager::gui::MemberHandler(this);
    QSignalSpy spy(handler, SIGNAL(memberChanged()));

    handler->onSelectedMemberId(2);
    membermanager::gui::ProxyTableModel *model = handler->balanceProxyModel();
    QCOMPARE(model->rowCount(), 1);
    QCOMPARE(spy.count(), 1);
}

void MemberHandlerTest::testMemberSelected()
{
    membermanager::gui::MemberHandler *handler = new membermanager::gui::MemberHandler(this);
    QSignalSpy spy(handler, SIGNAL(memberChanged()));

    handler->onSelectedMemberId(2);
    QCOMPARE(spy.count(), 1);
    membermanager::entity::Member *member = handler->member();
    QCOMPARE(member->name(), QString("McCoy"));

    QVariant memberVariant = handler->property("member");
    member = memberVariant.value<membermanager::entity::Member *>();
    QVariant nameVariant = member->property("name");
    QCOMPARE(nameVariant, QVariant("McCoy"));

    membermanager::entity::BankAccount *bankAccount = handler->bankAccount();
    QCOMPARE(bankAccount->name(), QString("Sparstrumpf"));

    membermanager::entity::Contribution *contribution = handler->contribution();
    double fee = 15.0;
    QCOMPARE(contribution->fee(), fee);
}

void MemberHandlerTest::testNewMember()
{
    membermanager::gui::MemberHandler *handler = new membermanager::gui::MemberHandler(this);
    QSignalSpy spy(handler, SIGNAL(memberChanged()));

    handler->onNewMember();

    QCOMPARE(spy.count(), 1);
    membermanager::entity::Member *member = handler->member();
    QCOMPARE(member->name(), QString(""));
}

void MemberHandlerTest::testNewContribution()
{
    membermanager::gui::MemberHandler *handler = new membermanager::gui::MemberHandler(this);
    QSignalSpy spy(handler, SIGNAL(memberChanged()));

    handler->onNewContribution();

    QCOMPARE(spy.count(), 1);
    membermanager::entity::Contribution* contribution = handler->contribution();
    QCOMPARE(contribution->fee(), 0.0);

}

}
}

QTEST_MAIN(test::gui::MemberHandlerTest)
#include "moc_memberhandlertest.cpp"
