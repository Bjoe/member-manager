
#include <QtTest/QtTest>
#include "testcoverageobject.h"

#include <QStackedLayout>

#include "gui/mainwindow.h"

#include "testconfig.h"
#include "database/databaseutil.h"

namespace membermanagertest
{
namespace gui
{

class MainWindowTest: public qttestutil::TestCoverageObject
{
    Q_OBJECT

private slots:
    void init();
    void testLoadDatabase();
};

void MainWindowTest::init()
{
    qttestutil::database::DatabaseUtil database(DATABASEDRIVER);
    database.open(DATABASE);
    database.read(SQLTESTFILE);
}

void MainWindowTest::testLoadDatabase()
{
    membermanager::gui::MainWindow mainWindow;

    QStackedWidget *stackedLayout = mainWindow.findChild<QStackedWidget *>("stackedLayout");
    int size = stackedLayout->count();

    mainWindow.loadDatabase();

    QCOMPARE(size, stackedLayout->count());
}

}
}

QTEST_MAIN(membermanagertest::gui::MainWindowTest)
#include "moc_mainwindowtest.cpp"
