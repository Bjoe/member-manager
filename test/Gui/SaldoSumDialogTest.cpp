#include "SaldoSumDialogTest.h"

#include "Gui/SaldoSumDialog.h"

#include "Model/SaldoSumModel.h"
#include "TestConfig.h"
#include "TestUtils/DatabaseUtils.h"

#include <QSqlDatabase>
#include <QTableView>
#include <QAbstractItemModel>

namespace ClubFrontendTest
{
namespace Gui
{

void SaldoSumDialogTest::initTestCase()
{
    Utils::DatabaseUtils database ( DATABASEDRIVER );
    database.open ( DATABASE );
    database.read ( SQLTESTFILE );
}

void SaldoSumDialogTest::testShowDialog()
{
    ClubFrontend::SaldoSumModel saldoSumModel ( QSqlDatabase::database() );
    ClubFrontend::SaldoSumDialog dialog ( saldoSumModel );

    QTableView* tableView = dialog.findChild<QTableView* > ( "tableView" );
    QAbstractItemModel* model = tableView->model();
    int rowCount = model->rowCount();
    QCOMPARE ( rowCount, 1 );
}

}
}

QTEST_MAIN ( ClubFrontendTest::Gui::SaldoSumDialogTest )
#include "SaldoSumDialogTest.moc"
