
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

#include "gui/memberlisthandler.h"
#include "gui/proxytablemodel.h"

namespace test {
namespace gui {

class MemberListHandlerTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testMemberProxyModelChanged();
    void testMemberSelected();
    void testMemberDeletedSelected();
};

void MemberListHandlerTest::initTestCase()
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

    QDjango::dropTables();
    QDjango::createTables();

    membermanager::entity::Member *member = new membermanager::entity::Member();
    member->setMemberId("1");
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

    member = new membermanager::entity::Member();
    member->setMemberId("2");
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

void MemberListHandlerTest::testMemberProxyModelChanged()
{
    membermanager::gui::MemberListHandler *handler = new membermanager::gui::MemberListHandler(this);
    QSignalSpy spy(handler, SIGNAL(memberProxyModelChanged()));

    membermanager::gui::ProxyTableModel *model = handler->memberProxyModel();
    QCOMPARE(model->rowCount(), 1);
    QCOMPARE(spy.count(), 0);

    handler->onRefresh("memberId", Qt::SortOrder::AscendingOrder);
    model = handler->memberProxyModel();
    QCOMPARE(model->rowCount(), 1);
    QCOMPARE(spy.count(), 1);
}

void MemberListHandlerTest::testMemberSelected()
{
    membermanager::gui::MemberListHandler *handler = new membermanager::gui::MemberListHandler(this);
    QSignalSpy spy(handler, SIGNAL(selectMemberId(QVariant)));

    handler->onSelectedRow(0);
    QCOMPARE(spy.count(), 1);

    QList<QVariant> arguments = spy.takeFirst();
    QCOMPARE(arguments.at(0).toString(), QString("2"));
}

void MemberListHandlerTest::testMemberDeletedSelected()
{
    membermanager::gui::MemberListHandler *handler = new membermanager::gui::MemberListHandler(this);
    QSignalSpy spy(handler, SIGNAL(selectMemberId(QVariant)));
    QSignalSpy spyState(handler, SIGNAL(memberStateChanged()));

    handler->setMemberState(membermanager::entity::Member::State::deleted);
    QCOMPARE(spyState.count(), 1);

    handler->onRefresh("memberId", Qt::SortOrder::AscendingOrder);

    handler->onSelectedRow(0);
    QCOMPARE(spy.count(), 1);

    QList<QVariant> arguments = spy.takeFirst();
    QCOMPARE(arguments.at(0).toString(), QString("1"));
}

}
}

QTEST_MAIN(test::gui::MemberListHandlerTest)
#include "moc_memberlisthandlertest.cpp"
