
#include <QtTest/QtTest>
#include "testcoverageobject.h"

#include <QApplication>
#include <QClipboard>
#include <QTableView>
#include <QModelIndex>
#include <QAbstractItemModel>
#include <QItemSelection>
#include <QItemSelectionModel>
#include <QLabel>
#include <QVariant>
#include <QString>
#include <QPushButton>

#include "testconfig.h"
#include "database/databaseutil.h"
#include "triggerthread.h"
#include "gui/dialogbuttonboxhandler.h"

#include "gui/balancedialog.h"

namespace membermanagertest
{
namespace gui
{

class BalanceDialogTest : public qttestutil::TestCoverageObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testShowDialog();
    void testWindowTitle();
    void testShowSum();
    void testInsertAndDeleteRow();
    void testCopyToClipboard();
};

void BalanceDialogTest::initTestCase()
{
    qttestutil::database::DatabaseUtil database(DATABASEDRIVER);
    database.open(DATABASE);
    database.read(SQLTESTFILE);
}

void BalanceDialogTest::testShowDialog()
{
    membermanager::gui::BalanceDialog dialog(1025);

    QTableView *tableView = dialog.findChild<QTableView *> ("balanceTableView");
    const QAbstractItemModel *model = tableView->model();
    QVERIFY(model != 0);
    QCOMPARE(model->rowCount(), 15);
    QModelIndex index = model->index(0, 3);
    QVariant value = model->data(index);
    QCOMPARE(value.toString(), QString("2012-02-10"));
}

void BalanceDialogTest::testWindowTitle()
{
    membermanager::gui::BalanceDialog dialog(1025);

    QCOMPARE(dialog.windowTitle(), QString("Member Id: 1025"));
}

void BalanceDialogTest::testShowSum()
{
    membermanager::gui::BalanceDialog dialog(1025);

    QLabel *sumLabel = dialog.findChild<QLabel *> ("sumLabel");
    QCOMPARE(sumLabel->text(), QString("Summe: -10"));
}

void BalanceDialogTest::testInsertAndDeleteRow()
{
    membermanager::gui::BalanceDialog dialog(1025);

    QTableView *tableView = dialog.findChild<QTableView *> ("balanceTableView");
    const QAbstractItemModel *model = tableView->model();
    QVERIFY(model != 0);
    QCOMPARE(model->rowCount(), 15);

    QPushButton *button = dialog.findChild<QPushButton *> ("newRowButton");
    QTest::mouseClick(button, Qt::LeftButton);

    QCOMPARE(model->rowCount(), 16);

    button = dialog.findChild<QPushButton *> ("deleteRowButton");
    QTest::mouseClick(button, Qt::LeftButton);

    QCOMPARE(model->rowCount(), 15);
}

void BalanceDialogTest::testCopyToClipboard()
{
    membermanager::gui::BalanceDialog dialog(1025);

    QTableView *tableView = dialog.findChild<QTableView *> ("balanceTableView");
    QItemSelectionModel *selectionModel = tableView->selectionModel();
    const QAbstractItemModel *model = tableView->model();
    QModelIndex topLeft = model->index(0, 0);
    QModelIndex bottomRight = model->index(1, 4);
    QItemSelection selection(topLeft, bottomRight);
    selectionModel->select(selection, QItemSelectionModel::Select);

    dialog.copy();

    QClipboard *clipboard = QApplication::clipboard();
    QCOMPARE(clipboard->text(), QString("21\t1025\t8\t2012-02-10\tZAHLUNGSEINGANG  1025 Ali Baba MITGLIEDSSCHULDEN\t\n"
                                        "15\t1025\t-5\t2012-02-08\tMitgliedsbeitrag Feb\t\n"));
}

} // namespace gui
} // namespace membermanagertest

QTEST_MAIN(membermanagertest::gui::BalanceDialogTest)
#include "moc_balancedialogtest.cpp"
