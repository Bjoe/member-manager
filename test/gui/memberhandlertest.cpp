
#include <QtTest/QtTest>

#include <QObject>
#include <QString>
#include <QSqlTableModel>

#include "QDjango.h"

#include "testconfig.h"

#include "entity/member.h"
#include "entity/contribution.h"
#include "entity/balance.h"
#include "entity/cashaccount.h"

#include "gui/memberhandler.h"
#include "gui/proxytablemodel.h"

namespace test {
namespace gui {

class MemberHandlerTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testHandler();
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

void MemberHandlerTest::testHandler()
{
    membermanager::gui::MemberHandler *handler = new membermanager::gui::MemberHandler(this);

    membermanager::gui::ProxyTableModel *model = handler->getProxyModel();

    QCOMPARE(model->rowCount(), 0);

    handler->onDatabaseReady();

    QCOMPARE(model->rowCount(), 1);
}

}
}

QTEST_MAIN(test::gui::MemberHandlerTest)
#include "moc_memberhandlertest.cpp"
