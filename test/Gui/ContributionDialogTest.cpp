#include "ContributionDialogTest.h"

#include "Gui/ContributionDialog.h"

#include "TestConfig.h"
#include "database/databaseutil.h"
#include "Model/DatabaseStructure.h"
#include "Model/ContributionModel.h"

#include <QSqlDatabase>
#include <QTableView>
#include <QModelIndex>
#include <QAbstractItemModel>
#include <QPoint>
#include <QVariant>
#include <QString>

namespace ClubFrontendTest
{
namespace Gui
{

void ContributionDialogTest::initTestCase()
{
    qttestutil::database::DatabaseUtil database ( DATABASEDRIVER );
    database.open ( DATABASE );
    database.read ( SQLTESTFILE );
}

void ContributionDialogTest::testShowDialog()
{
    ClubFrontend::Model::ContributionModel contributionModel ( QSqlDatabase::database() );
    contributionModel.setMemberId ( 1025 );
    ClubFrontend::Gui::ContributionDialog dialog ( &contributionModel );

    const QTableView* tableView = dialog.findChild<QTableView* > ( "contributionTableView" );
    const QAbstractItemModel* model = tableView->model();
    QVERIFY ( model != 0 );
    QCOMPARE ( model->rowCount(), 2 );
    using ClubFrontend::Model::ContributionTable;
    const QModelIndex index = model->index ( 0, ContributionTable::ValidFrom );
    const QVariant value = model->data ( index );
    QCOMPARE ( value.toString(), QString ( "2007-05-01" ) );
}


}
}

QTEST_MAIN ( ClubFrontendTest::Gui::ContributionDialogTest )
#include "ContributionDialogTest.moc"
