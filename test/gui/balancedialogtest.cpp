#include "balancedialogtest.h"

#include "gui/balancedialog.h"

#include <QTableView>
#include <QModelIndex>
#include <QAbstractItemModel>
#include <QLabel>
#include <QVariant>
#include <QString>
#include <QPushButton>

#include "testconfig.h"
#include "database/databaseutil.h"
#include "triggerthread.h"
#include "gui/dialogbuttonboxhandler.h"

namespace membermanagertest
{
namespace gui
{

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

} // namespace gui
} // namespace membermanagertest

QTEST_MAIN(membermanagertest::gui::BalanceDialogTest)
#include "balancedialogtest.moc"
