#include "contributiondialogtest.h"

#include "gui/contributiondialog.h"

#include "testconfig.h"
#include "database/databaseutil.h"
#include "model/databasestructure.h"
#include "model/contributionmodel.h"

#include <QSqlDatabase>
#include <QTableView>
#include <QModelIndex>
#include <QAbstractItemModel>
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
    membermanager::model::ContributionModel contributionModel(1025, QSqlDatabase::database());
    membermanager::gui::ContributionDialog dialog(&contributionModel);

    const QTableView *tableView = dialog.findChild<QTableView *> ("contributionTableView");
    const QAbstractItemModel *model = tableView->model();
    QVERIFY(model != 0);
    QCOMPARE(model->rowCount(), 2);
    using membermanager::model::ContributionTable;
    const QModelIndex index = model->index(0, ContributionTable::ValidFrom);
    const QVariant value = model->data(index);
    QCOMPARE(value.toString(), QString("2007-05-01"));
}


}
}

QTEST_MAIN(membermanagertest::gui::ContributionDialogTest)
#include "contributiondialogtest.moc"
