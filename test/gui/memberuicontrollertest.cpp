#include <QtTest/QtTest>

#include <QObject>
#include <QString>
#include <QSignalSpy>
#include <QSqlTableModel>

#include "QDjango.h"

#include "testconfig.h"

#include "entity/member.h"
#include "entity/contribution.h"
#include "entity/balance.h"
#include "entity/cashaccount.h"

#include "gui/memberuicontroller.h"

namespace test {
namespace gui {

class MemberUiControllerTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testOnDatabaseReady();

};

void MemberUiControllerTest::initTestCase()
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
    QDjango::registerModel<membermanager::entity::Balance>();
    QDjango::registerModel<membermanager::entity::CashAccount>();

    QDjango::dropTables();
    QDjango::createTables();

    membermanager::entity::Member *member = new membermanager::entity::Member();
    member->setName("Kirk");
    member->setFirstname("James T.");
    member->setEmail("enterprise@startrek.com");
    member->setEntryDate(QDate(2013,8,10));
    member->setStreet("universe");
    member->setCity("NCC");
    member->setZipCode("1701");
    member->setCollection(false);
    member->setDeleted(false);
    member->save();

    db.close();
}

void MemberUiControllerTest::testOnDatabaseReady()
{
    membermanager::gui::MemberUiController uiController(this);

    QSqlTableModel *model = qobject_cast<QSqlTableModel *>(uiController.memberTableModel());
    QCOMPARE(model->rowCount(), 0);

    QSignalSpy spy(&uiController, SIGNAL(memberTableModelChanged()));
    uiController.onDatabaseReady();

    QCOMPARE(spy.count(), 1);

    QCOMPARE(model->rowCount(), 1);
}

}
}

QTEST_MAIN(test::gui::MemberUiControllerTest)
#include "moc_memberuicontrollertest.cpp"

