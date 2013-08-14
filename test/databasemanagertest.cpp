
#include <QtTest/QtTest>

#include <QtCore/QObject>
#include <QtCore/QString>

#include "QDjango.h"

#include "testconfig.h"

#include "entity/member.h"
#include "entity/contribution.h"
#include "entity/balance.h"
#include "entity/cashaccount.h"

#include "databasemanager.h"

namespace test {

class DatabaseManagerTest : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void testLoadDatabase();

};

void DatabaseManagerTest::init()
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

    db.close();
}

void DatabaseManagerTest::testLoadDatabase()
{
    QString filename = "file:" DATABASE;
    membermanager::DatabaseManager databaseManager(this);
    databaseManager.onLoadSqlFile(filename);
}

}

QTEST_MAIN(test::DatabaseManagerTest)
#include "moc_databasemanagertest.cpp"
