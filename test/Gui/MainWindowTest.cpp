
#include "MainWindowTest.h"

#include "Gui/MainWindow.h"

#include "TestConfig.h"
#include "TestUtils/DatabaseUtils.h"
#include "TestUtils/TriggerThread.h"
#include "TestUtils/DialogButtonBoxHandler.h"
#include "Model/MemberModel.h"

#include <QTableView>
#include <QSqlTableModel>
#include <QModelIndex>
#include <QAbstractItemModel>
#include <QVariant>
#include <QAction>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QApplication>
#include <QSqlTableModel>
#include <QModelIndex>
#include <QItemSelection>
#include <QItemSelectionModel>
#include <QClipboard>
#include <QApplication>
#include <QLabel>

#include <QDebug>

namespace ClubFrontendTest
{
namespace Gui
{

void MainWindowTest::init()
{
    Utils::DatabaseUtils database ( DATABASEDRIVER );
    database.open ( DATABASE );
    database.read ( SQLTESTFILE );
}

void MainWindowTest::testNewMember()
{
    ClubFrontend::Model::KassaModel kassaModel ( QSqlDatabase::database() );
    ClubFrontend::Model::MemberModel memberModel ( QSqlDatabase::database() );
    ClubFrontend::Gui::MainWindow mainWindow ( memberModel, kassaModel );

    QAction* actionNewMember = mainWindow.findChild<QAction*> (
                                   "actionNewMember" );
    Utils::TriggerThread thread ( this, this );
    connect ( &thread, SIGNAL ( triggered() ), actionNewMember, SLOT ( trigger() ) );
    thread.syncStart();

    QAction* actionShowDeletedMember = mainWindow.findChild<QAction*> (
                                           "actionShowDeletedMember" );
    actionShowDeletedMember->trigger();

    QTableView* view = mainWindow.findChild<QTableView* > ( "tableView" );
    QAbstractItemModel* model = view->model();
    QCOMPARE ( model->rowCount(), 2 );

    QCOMPARE ( id, QString ( "1027" ) );
}

void MainWindowTest::testEditMember()
{
    ClubFrontend::Model::KassaModel kassaModel ( QSqlDatabase::database() );
    ClubFrontend::Model::MemberModel memberModel ( QSqlDatabase::database() );
    ClubFrontend::Gui::MainWindow mainWindow ( memberModel, kassaModel );

    QTableView* view = mainWindow.findChild<QTableView* > ( "tableView" );
    QAbstractItemModel* model = view->model();
    QModelIndex index = model->index ( 0, 3 );

    Utils::TriggerThread thread ( this, this, index );
    connect ( &thread, SIGNAL ( triggeredModelIndex ( const QModelIndex& ) ), &mainWindow, SLOT ( editMember ( const QModelIndex& ) ) );
    thread.syncStart();

    QCOMPARE ( id, QString ( "1025" ) );
}

void MainWindowTest::testSelectedMember()
{
    ClubFrontend::Model::KassaModel kassaModel ( QSqlDatabase::database() );
    ClubFrontend::Model::MemberModel memberModel ( QSqlDatabase::database() );
    ClubFrontend::Gui::MainWindow mainWindow ( memberModel, kassaModel );

    QTableView* view = mainWindow.findChild<QTableView* > ( "tableView" );
    QItemSelectionModel* selectionModel = view->selectionModel();
    QAbstractItemModel* model = view->model();
    QModelIndex index = model->index ( 0,3 );
    QItemSelection selection ( index, index );
    selectionModel->select ( selection, QItemSelectionModel::Select );

    Utils::TriggerThread thread ( this, this );
    connect ( &thread, SIGNAL ( triggered() ), &mainWindow, SLOT ( selectedMember() ) );
    thread.syncStart();

    QCOMPARE ( id, QString ( "1025" ) );
}

void MainWindowTest::testShowSaldo()
{
    ClubFrontend::Model::KassaModel kassaModel ( QSqlDatabase::database() );
    ClubFrontend::Model::MemberModel memberModel ( QSqlDatabase::database() );
    ClubFrontend::Gui::MainWindow mainWindow ( memberModel, kassaModel );

    QTableView* view = mainWindow.findChild<QTableView* > ( "tableView" );
    QItemSelectionModel* selectionModel = view->selectionModel();
    QAbstractItemModel* model = view->model();
    QModelIndex index = model->index ( 0, 3 );
    QItemSelection selection ( index, index );
    selectionModel->select ( selection, QItemSelectionModel::Select );

    Utils::DialogButtonBoxHandler handler ( QDialogButtonBox::Close );
    Utils::TriggerThread thread ( this, &handler );
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
    ClubFrontend::Model::KassaModel kassaModel ( QSqlDatabase::database() );
    ClubFrontend::Model::MemberModel memberModel ( QSqlDatabase::database() );
    ClubFrontend::Gui::MainWindow mainWindow ( memberModel, kassaModel );

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

    // XXX QTest::mouseClick(view, Qt::LeftButton, Qt::NoModifier, QPoint(0,0));
    // XXX QModelIndex index = view->currentIndex();
}

void MainWindowTest::testDeletedMemberView()
{
    ClubFrontend::Model::KassaModel kassaModel ( QSqlDatabase::database() );
    ClubFrontend::Model::MemberModel memberModel ( QSqlDatabase::database() );
    ClubFrontend::Gui::MainWindow mainWindow ( memberModel, kassaModel );

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

    // XXX QTest::mouseClick(view, Qt::LeftButton, Qt::NoModifier, QPoint(0,0));
    // XXX QModelIndex index = view->currentIndex();
}

void MainWindowTest::testShowKassaView()
{
    ClubFrontend::Model::KassaModel kassaModel ( QSqlDatabase::database() );
    ClubFrontend::Model::MemberModel memberModel ( QSqlDatabase::database() );
    ClubFrontend::Gui::MainWindow mainWindow ( memberModel, kassaModel );

    QAction* actionShowKassa = mainWindow.findChild<QAction*> (
                                   "actionShowKassa" );
    actionShowKassa->trigger();

    QAction* actionSelectMember = mainWindow.findChild<QAction*> (
                                      "actionShowMember" );
    QVERIFY ( !actionSelectMember->isChecked() );

    QAction* actionShowDeletedMember = mainWindow.findChild<QAction*> (
                                           "actionShowDeletedMember" );
    QVERIFY ( !actionShowDeletedMember->isChecked() );

    QTableView* view = mainWindow.findChild<QTableView*> ( "tableView" );

    QModelIndex index = view->indexAt ( QPoint ( 0, 0 ) );
    QVERIFY ( index.isValid() );
    const QAbstractItemModel * model = index.model();
    QVERIFY ( model != 0 );
    QCOMPARE ( model->rowCount(), 3 );
    QVariant value = model->data ( index );
    QCOMPARE ( value.toString(), QString ( "" ) );
}

}
}

QTEST_MAIN ( ClubFrontendTest::Gui::MainWindowTest )
#include "MainWindowTest.moc"
