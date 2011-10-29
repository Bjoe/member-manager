#include "saldosumdialogtest.h"

#include "gui/saldosumdialog.h"

#include "model/saldosummodel.h"
#include "testconfig.h"
#include "testutil/databaseutils.h"

#include <QSqlDatabase>
#include <QTableView>
#include <QAbstractItemModel>

namespace ClubFrontendTest
{
namespace Gui
{

void SaldoSumDialogTest::initTestCase()
{
    Utils::DatabaseUtils database(DATABASEDRIVER);
    database.open(DATABASE);
    database.read(SQLTESTFILE);
}

void SaldoSumDialogTest::testShowDialog()
{
    ClubFrontend::SaldoSumModel saldoSumModel(QSqlDatabase::database());
    ClubFrontend::SaldoSumDialog dialog(saldoSumModel);

    QTableView *tableView = dialog.findChild<QTableView * > ("tableView");
    QAbstractItemModel *model = tableView->model();
    int rowCount = model->rowCount();
    QCOMPARE(rowCount, 1);
}

}
}

QTEST_MAIN(ClubFrontendTest::Gui::SaldoSumDialogTest)
#include "saldosumdialogtest.moc"
