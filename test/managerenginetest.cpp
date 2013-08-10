
#include <QtTest/QtTest>

#include <QtCore/QObject>
#include <QtCore/QString>

#include "QDjango.h"

#include "testconfig.h"

#include "entity/member.h"

#include "managerengine.h"

namespace test {

class ManagerEngineTest : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void testLoadDatabase();

};

void ManagerEngineTest::init()
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

    db.close();
}

void ManagerEngineTest::testLoadDatabase()
{
    QString filename = "file:" DATABASE;
    membermanager::ManagerEngine managerEngine(this);
    managerEngine.onLoadSqlFile(filename);
}

}

QTEST_MAIN(test::ManagerEngineTest)
#include "moc_managerenginetest.cpp"
