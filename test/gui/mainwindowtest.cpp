
#include "mainwindowtest.h"

#include "gui/mainwindow.h"

#include "testconfig.h"
#include "database/databaseutil.h"
#include "triggerthread.h"
#include "gui/dialogbuttonboxhandler.h"
#include "model/membermodel.h"

#include <QtSql>
#include <QtGui>
#include <QTest>
#include <QDebug>

namespace ClubFrontendTest
{
namespace Gui
{

void MainWindowTest::init()
{
    qttestutil::database::DatabaseUtil database ( DATABASEDRIVER );
    database.open ( DATABASE );
    database.read ( SQLTESTFILE );
}

void MainWindowTest::testNewMember()
{
    ClubFrontend::Gui::MainWindow mainWindow ( QSqlDatabase::database() );

    QAction* actionNewMember = mainWindow.findChild<QAction*> (
                                   "actionNewMember" );
    actionNewMember->trigger();

    QAction* actionShowDeletedMember = mainWindow.findChild<QAction*> (
                                           "actionShowDeletedMember" );
    actionShowDeletedMember->trigger();

    QTableView* view = mainWindow.findChild<QTableView* > ( "tableView" );
    QAbstractItemModel* model = view->model();
    QCOMPARE ( model->rowCount(), 2 );
}


void MainWindowTest::testSelectedMember()
{
    ClubFrontend::Gui::MainWindow mainWindow ( QSqlDatabase::database() );

    QTableView* view = mainWindow.findChild<QTableView* > ( "tableView" );
    QItemSelectionModel* selectionModel = view->selectionModel();
    QAbstractItemModel* model = view->model();
    QModelIndex index = model->index ( 0,3 );
    QItemSelection selection ( index, index );
    selectionModel->select ( selection, QItemSelectionModel::Select );

    QLabel *memberId = mainWindow.findChild<QLabel* >( "memberId" );
    QCOMPARE (memberId->text() , QString ( "1025" ) );
}

void MainWindowTest::testShowSaldo()
{
    ClubFrontend::Gui::MainWindow mainWindow ( QSqlDatabase::database() );

    QTableView* view = mainWindow.findChild<QTableView* > ( "tableView" );
    QItemSelectionModel* selectionModel = view->selectionModel();
    QAbstractItemModel* model = view->model();
    QModelIndex index = model->index ( 0, 3 );
    QItemSelection selection ( index, index );
    selectionModel->select ( selection, QItemSelectionModel::Select );

    qttestutil::gui::DialogButtonBoxHandler handler ( QDialogButtonBox::Close );
    qttestutil::TriggerThread thread ( this, &handler );
    connect ( &thread, SIGNAL ( triggered() ), &mainWindow, SLOT ( showSaldo() ) );
    thread.syncStart();
}

void MainWindowTest::handle()
{
    bool next = true;
    do
    {
        QWidget* widget = QApplication::activeWindow();
        if ( widget )
        {
            QLabel* memberId = widget->findChild<QLabel* > ( "memberId" );
            id = memberId->text();
            QDialogButtonBox* buttonBox = widget->findChild<QDialogButtonBox*> (
                                              "buttonBox" );
            QPushButton* button = buttonBox->button ( QDialogButtonBox::Close );
            button->click();
            next = false;
        }
    }
    while ( next );
}

void MainWindowTest::testMemberView()
{
    ClubFrontend::Gui::MainWindow mainWindow ( QSqlDatabase::database() );

    QAction* actionSelectMember = mainWindow.findChild<QAction*> (
                                      "actionShowMember" );
    actionSelectMember->trigger();

    QAction* actionShowDeletedMember = mainWindow.findChild<QAction*> (
                                           "actionShowDeletedMember" );
    QVERIFY ( !actionShowDeletedMember->isChecked() );

    QTableView* view = mainWindow.findChild<QTableView*> ( "tableView" );

    QModelIndex index = view->indexAt ( QPoint ( 0, 0 ) );
    QVERIFY ( index.isValid() );
    const QAbstractItemModel * model = index.model();
    QVERIFY ( model != 0 );
    QCOMPARE ( model->rowCount(), 1 );
    QVariant value = model->data ( index );
    QCOMPARE ( value.toInt(),1025 );

    // \todo QTest::mouseClick(view, Qt::LeftButton, Qt::NoModifier, QPoint(0,0));
    // \todo QModelIndex index = view->currentIndex();
}

void MainWindowTest::testDeletedMemberView()
{
    ClubFrontend::Gui::MainWindow mainWindow ( QSqlDatabase::database() );

    QAction* actionShowDeletedMember = mainWindow.findChild<QAction*> (
                                           "actionShowDeletedMember" );
    actionShowDeletedMember->trigger();

    QAction* actionSelectMember = mainWindow.findChild<QAction*> (
                                      "actionShowMember" );
    QVERIFY ( !actionSelectMember->isChecked() );

    QTableView* view = mainWindow.findChild<QTableView*> ( "tableView" );

    QModelIndex index = view->indexAt ( QPoint ( 0, 0 ) );
    QVERIFY ( index.isValid() );
    const QAbstractItemModel * model = index.model();
    QVERIFY ( model != 0 );
    QCOMPARE ( model->rowCount(), 1 );
    QVariant value = model->data ( index );
    QCOMPARE ( value.toInt(),1026 );

    // \todo QTest::mouseClick(view, Qt::LeftButton, Qt::NoModifier, QPoint(0,0));
    // \todo QModelIndex index = view->currentIndex();
}

}
}

QTEST_MAIN ( ClubFrontendTest::Gui::MainWindowTest )
#include "mainwindowtest.moc"
