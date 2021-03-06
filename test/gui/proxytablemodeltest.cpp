
#include <QtTest/QtTest>
#include <QSignalSpy>

#include <QObject>
#include <QString>
#include <QByteArray>
#include <QHash>
#include <QModelIndex>
#include <QSqlTableModel>

#include "QDjango.h"

#include "testconfig.h"

#include "entity/member.h"

#include "gui/proxytablemodel.h"

namespace test {
namespace gui {

class ProxyTableModelTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testProxy();
};

void ProxyTableModelTest::initTestCase()
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
    member->setName("Kirk");
    member->setFirstname("James T.");
    member->setEmail("enterprise@startrek.com");
    member->setEntryDate(QDate(2013,8,10));
    member->setStreet("universe");
    member->setCity("NCC");
    member->setZipCode("1701");
    member->save();
}

void ProxyTableModelTest::testProxy()
{
    QSqlTableModel *model = new QSqlTableModel();
    model->setTable("member");
    model->select();

    membermanager::gui::ProxyTableModel proxyTable(this);
    proxyTable.setModel(model);
    QHash<int, QByteArray> roles = proxyTable.roleNames();

    QCOMPARE(roles.size(), 15);

    QCOMPARE(roles.value(Qt::UserRole + 2).data(), "memberId");
    QCOMPARE(roles.value(Qt::UserRole + 3).data(), "name");

    QModelIndex index = proxyTable.index(0, 0);
    QVariant value = proxyTable.data(index, Qt::UserRole + 4);
    QCOMPARE(value, QVariant("James T."));
}

}
}

QTEST_MAIN(test::gui::ProxyTableModelTest)
#include "moc_proxytablemodeltest.cpp"

