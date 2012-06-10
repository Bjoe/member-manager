
#include "mainwindowtest.h"

#include "gui/mainwindow.h"

#include "testconfig.h"
#include "database/databaseutil.h"

#include <QtSql>
#include <QtGui>
#include <QTest>
#include <QDebug>

namespace membermanagertest
{
namespace gui
{

void MainWindowTest::init()
{
    qttestutil::database::DatabaseUtil database(DATABASEDRIVER);
    database.open(DATABASE);
    database.read(SQLTESTFILE);
}

}
}

QTEST_MAIN(membermanagertest::gui::MainWindowTest)
#include "mainwindowtest.moc"
