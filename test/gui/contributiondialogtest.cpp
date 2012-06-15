#include "contributiondialogtest.h"

#include "gui/contributiondialog.h"

#include "testconfig.h"
#include "database/databaseutil.h"
#include "dao/databasestructure.h"

#include <QTableView>
#include <QModelIndex>
#include <QAbstractItemModel>
#include <QPushButton>
#include <QVariant>
#include <QString>

namespace membermanagertest
{
namespace gui
{

void ContributionDialogTest::initTestCase()
{
    qttestutil::database::DatabaseUtil database(DATABASEDRIVER);
    database.open(DATABASE);
    database.read(SQLTESTFILE);
}

void ContributionDialogTest::testShowDialog()
{
    membermanager::gui::ContributionDialog dialog(1025);

    const QTableView *tableView = dialog.findChild<QTableView *> ("contributionTableView");
    const QAbstractItemModel *model = tableView->model();
    QVERIFY(model != 0);
    QCOMPARE(model->rowCount(), 7);
    using membermanager::dao::ContributionTable;
    const QModelIndex index = model->index(0, ContributionTable::ValidFrom);
    const QVariant value = model->data(index);
    QCOMPARE(value.toString(), QString("2009-03-10"));
}

void ContributionDialogTest::testWindowTitle()
{
    membermanager::gui::ContributionDialog dialog(1025);

    QCOMPARE(dialog.windowTitle(), QString("Member Id: 1025"));
}

void ContributionDialogTest::testInsertAndDeleteRow()
{
    membermanager::gui::ContributionDialog dialog(1025);

    const QTableView *tableView = dialog.findChild<QTableView *> ("contributionTableView");
    const QAbstractItemModel *model = tableView->model();
    QVERIFY(model != 0);
    QCOMPARE(model->rowCount(), 7);

    QPushButton *button = dialog.findChild<QPushButton *> ("newRowButton");
    QTest::mouseClick(button, Qt::LeftButton);

    QCOMPARE(model->rowCount(), 8);


    button = dialog.findChild<QPushButton *> ("deleteRowButton");
    QTest::mouseClick(button, Qt::LeftButton);

    QCOMPARE(model->rowCount(), 7);
}

}
}

QTEST_MAIN(membermanagertest::gui::ContributionDialogTest)
#include "contributiondialogtest.moc"
