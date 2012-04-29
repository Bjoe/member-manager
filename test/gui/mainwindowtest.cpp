
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

void MainWindowTest::testNewMember()
{
    membermanager::gui::MainWindow mainWindow(QSqlDatabase::database());
    QTableView *view = mainWindow.findChild<QTableView *> ("tableView");
    QAbstractItemModel *model = view->model();
    QCOMPARE(model->rowCount(), 1);

    QAction *actionNewMember = mainWindow.findChild<QAction *> (
                                   "actionNewMember");
    actionNewMember->trigger();

    QAction *actionShowDeletedMember = mainWindow.findChild<QAction *> (
                                           "actionShowDeletedMember");
    actionShowDeletedMember->trigger();

    view = mainWindow.findChild<QTableView *> ("tableView");
    model = view->model();
    QCOMPARE(model->rowCount(), 2);
}


void MainWindowTest::testSelectedMember()
{
    membermanager::gui::MainWindow mainWindow(QSqlDatabase::database());

    QTableView *view = mainWindow.findChild<QTableView *> ("tableView");
    QItemSelectionModel *selectionModel = view->selectionModel();
    QAbstractItemModel *model = view->model();
    QModelIndex index = model->index(0, 3);
    QItemSelection selection(index, index);
    selectionModel->select(selection, QItemSelectionModel::Select);

    QLabel *memberId = mainWindow.findChild<QLabel *>("memberId");
    QCOMPARE(memberId->text() , QString("1025"));
}


void MainWindowTest::testMemberView()
{
    membermanager::gui::MainWindow mainWindow(QSqlDatabase::database());

    QAction *actionSelectMember = mainWindow.findChild<QAction *> (
                                      "actionShowMember");
    actionSelectMember->trigger();

    QAction *actionShowDeletedMember = mainWindow.findChild<QAction *> (
                                           "actionShowDeletedMember");
    QVERIFY(!actionShowDeletedMember->isChecked());

    QTableView *view = mainWindow.findChild<QTableView *> ("tableView");

    QModelIndex index = view->indexAt(QPoint(0, 0));
    QVERIFY(index.isValid());
    const QAbstractItemModel *model = index.model();
    QVERIFY(model != 0);
    QCOMPARE(model->rowCount(), 1);
    QVariant value = model->data(index);
    QCOMPARE(value.toInt(), 1025);

    // \todo QTest::mouseClick(view, Qt::LeftButton, Qt::NoModifier, QPoint(0,0));
    // \todo QModelIndex index = view->currentIndex();
}

void MainWindowTest::testDeletedMemberView()
{
    membermanager::gui::MainWindow mainWindow(QSqlDatabase::database());

    QAction *actionShowDeletedMember = mainWindow.findChild<QAction *> (
                                           "actionShowDeletedMember");
    actionShowDeletedMember->trigger();

    QAction *actionSelectMember = mainWindow.findChild<QAction *> (
                                      "actionShowMember");
    QVERIFY(!actionSelectMember->isChecked());

    QTableView *view = mainWindow.findChild<QTableView *> ("tableView");

    QModelIndex index = view->indexAt(QPoint(0, 0));
    QVERIFY(index.isValid());
    const QAbstractItemModel *model = index.model();
    QVERIFY(model != 0);
    QCOMPARE(model->rowCount(), 1);
    QVariant value = model->data(index);
    QCOMPARE(value.toInt(), 1026);

    // \todo QTest::mouseClick(view, Qt::LeftButton, Qt::NoModifier, QPoint(0,0));
    // \todo QModelIndex index = view->currentIndex();
}

}
}

QTEST_MAIN(membermanagertest::gui::MainWindowTest)
#include "mainwindowtest.moc"
