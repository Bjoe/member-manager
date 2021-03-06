
#include <QtTest/QtTest>
#include <QObject>
#include <QString>
#include <QList>

#include <QSqlTableModel>

#include "QDjango.h"

#include "testconfig.h"

#include "entity/member.h"

#include "dao/membertablemodel.h"

namespace test {
namespace dao {

class MemberTableModelTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testCreateTableModel();
    void testGiveMemberIdFromRow();
    void testFindMemberByRow();
    void testSelectState();
    void testFindByState();
};

void MemberTableModelTest::initTestCase()
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
    member->setCollectionState(membermanager::entity::Member::CollectionState::notKnown);
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

void MemberTableModelTest::testCreateTableModel()
{
    QSqlTableModel *model = membermanager::dao::MemberTableModel::createModel(membermanager::entity::Member::State::active, "memberId", Qt::SortOrder::AscendingOrder);
    QCOMPARE(model->rowCount(), 1);
}

void MemberTableModelTest::testGiveMemberIdFromRow()
{
    QSqlTableModel *model = membermanager::dao::MemberTableModel::createModel(membermanager::entity::Member::State::active, "memberId", Qt::SortOrder::AscendingOrder);
    QVariant memberId =
            membermanager::dao::MemberTableModel::giveMemberIdByRow(model, 0);
    QCOMPARE(memberId.toString(), QString("2"));
}

void MemberTableModelTest::testFindMemberByRow()
{
    membermanager::entity::Member *member =
            membermanager::dao::MemberTableModel::findByMemberId(1);

    QCOMPARE(member->name(), QString("Kirk"));
}

void MemberTableModelTest::testSelectState()
{
    QSqlTableModel *model = membermanager::dao::MemberTableModel::createModel(membermanager::entity::Member::State::active, "memberId", Qt::SortOrder::AscendingOrder);
    QVariant memberId =
            membermanager::dao::MemberTableModel::giveMemberIdByRow(model, 0);

    QCOMPARE(memberId.toString(), QString("2"));

    membermanager::dao::MemberTableModel::selectState(model, membermanager::entity::Member::State::deleted);

    memberId = membermanager::dao::MemberTableModel::giveMemberIdByRow(model, 0);
    QCOMPARE(memberId.toString(), QString("1"));
}

void MemberTableModelTest::testFindByState()
{
    QList<membermanager::entity::Member *> members = membermanager::dao::MemberTableModel::findByState(membermanager::entity::Member::State::active);
    QCOMPARE(members.size(), 1);
}

}
}

QTEST_MAIN(test::dao::MemberTableModelTest)
#include "moc_membertablemodeltest.cpp"
