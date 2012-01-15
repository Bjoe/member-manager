#include "contributiondialogtest.h"

#include "gui/contributiondialog.h"

#include "testconfig.h"
#include "database/databaseutil.h"
#include "model/databasestructure.h"
#include "model/contributionmodel.h"
#include "model/memberfilter.h"

#include <QSqlDatabase>
#include <QTableView>
#include <QModelIndex>
#include <QAbstractItemModel>
#include <QPushButton>
#include <QPoint>
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
    using membermanager::model::MemberFilter;
    membermanager::model::ContributionModel contributionModel(1025, QSqlDatabase::database());
    membermanager::gui::ContributionDialog dialog(contributionModel);

    const QTableView *tableView = dialog.findChild<QTableView *> ("contributionTableView");
    const QAbstractItemModel *model = tableView->model();
    QVERIFY(model != 0);
    QCOMPARE(model->rowCount(), 2);
    using membermanager::model::ContributionTable;
    const QModelIndex index = model->index(0, ContributionTable::ValidFrom -1);
    const QVariant value = model->data(index);
    QCOMPARE(value.toString(), QString("2007-05-01"));
}

void ContributionDialogTest::testWindowTitle()
{
    using membermanager::model::MemberFilter;
    membermanager::model::ContributionModel contributionModel(1025, QSqlDatabase::database());
    membermanager::gui::ContributionDialog dialog(contributionModel);

    QCOMPARE(dialog.windowTitle(), QString("Member Id: 1025"));
}

void ContributionDialogTest::testInsertAndDeleteRow()
{
    using membermanager::model::MemberFilter;
    membermanager::model::ContributionModel contributionModel(1025, QSqlDatabase::database());
    membermanager::gui::ContributionDialog dialog(contributionModel);

    const QTableView *tableView = dialog.findChild<QTableView *> ("contributionTableView");
    const QAbstractItemModel *model = tableView->model();
    QVERIFY(model != 0);
    QCOMPARE(model->rowCount(), 2);

    QPushButton *button = dialog.findChild<QPushButton *> ("newRowButton");
    QTest::mouseClick(button, Qt::LeftButton);

    QCOMPARE(model->rowCount(), 3);


    button = dialog.findChild<QPushButton *> ("deleteRowButton");
    QTest::mouseClick(button, Qt::LeftButton);

    QCOMPARE(model->rowCount(), 2);
}

}
}

QTEST_MAIN(membermanagertest::gui::ContributionDialogTest)
#include "contributiondialogtest.moc"
