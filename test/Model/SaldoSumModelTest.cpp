#include "SaldoSumModelTest.h"

#include "Model/SaldoSumModel.h"

#include "TestConfig.h"
#include "database/databaseutil.h"
#include "Model/DatabaseStructure.h"

#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QSqlRecord>
#include <QVariant>
#include <QString>

namespace ClubFrontendTest
{
namespace Model
{

void SaldoSumModelTest::initTestCase()
{
    qttestutil::database::DatabaseUtil database ( DATABASEDRIVER );
    database.open ( DATABASE );
    database.read ( SQLTESTFILE );
}

void SaldoSumModelTest::testView()
{
    ClubFrontend::Model::SaldoSumModel saldoSumModel ( QSqlDatabase::database() );
    QTableView* view = new QTableView();
    saldoSumModel.initTableView ( view );
    QAbstractItemModel* model = view->model();
    QVariant variant = model->data ( model->index ( 0,1 ) );
    QCOMPARE ( variant.toString(), QString ( "Capt. Kirk" ) );
}

}
}

QTEST_MAIN ( ClubFrontendTest::Model::SaldoSumModelTest )
#include "SaldoSumModelTest.moc"
