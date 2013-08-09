
#include <QtTest/QtTest>

#include <QtCore/QString>

#include "testconfig.h"
#include "testcoverageobject.h"
#include "database/databaseutil.h"

#include "managerengine.h"

namespace test {

class ManagerEngineTest : public qttestutil::TestCoverageObject
{
    Q_OBJECT

private slots:
    void init();
    void testLoadDatabase();

};

void ManagerEngineTest::init()
{
    qttestutil::database::DatabaseUtil database(DATABASEDRIVER);
    database.open(DATABASE);
    database.read(SQLTESTFILE);
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
