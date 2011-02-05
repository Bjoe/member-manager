#include "SaldoDialogTest.h"

#include "Gui/SaldoDialog.h"

#include "TestConfig.h"
#include "TestUtils/DatabaseUtils.h"
#include "Model/SaldoModel.h"

#include <QSqlDatabase>
#include <QTableView>
#include <QModelIndex>
#include <QAbstractItemModel>
#include <QPoint>
#include <QVariant>
#include <QString>
#include <QLabel>

#include <QDebug>

namespace ClubFrontendTest
{
namespace Gui
{

void SaldoDialogTest::initTestCase()
{
    Utils::DatabaseUtils database ( DATABASEDRIVER );
    database.open ( DATABASE );
    database.read ( SQLTESTFILE );
}

void SaldoDialogTest::testShowDialog()
{
    ClubFrontend::Model::SaldoModel saldoModel ( QSqlDatabase::database(), 1025 );
    ClubFrontend::Gui::SaldoDialog dialog ( saldoModel );

    QTableView* tableView = dialog.findChild<QTableView* > ( "saldoTableView" );
    const QAbstractItemModel* model = tableView->model();
    QVERIFY ( model != 0 );
    QCOMPARE ( model->rowCount(), 2 );
    QModelIndex index = model->index ( 0,3 );
    QVariant value = model->data ( index );
    QCOMPARE ( value.toString(), QString ( "2005-09-18" ) );
}

void SaldoDialogTest::testShowSum()
{
    ClubFrontend::Model::SaldoModel saldoModel ( QSqlDatabase::database(), 1025 );
    ClubFrontend::Gui::SaldoDialog dialog ( saldoModel );

    QLabel* sumLabel = dialog.findChild<QLabel* > ( "sumLabel" );
    QCOMPARE ( sumLabel->text(), QString ( "Summe: -15" ) );
}

}
}

QTEST_MAIN ( ClubFrontendTest::Gui::SaldoDialogTest )
#include "SaldoDialogTest.moc"
