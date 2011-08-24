#include "saldomodeltest.h"

#include "model/saldomodel.h"

#include "testconfig.h"
#include "database/databaseutil.h"
#include "model/databasestructure.h"

#include <QSqlTableModel>
#include <QSqlRecord>
#include <QString>

namespace ClubFrontendTest
{
namespace Model
{

void SaldoModelTest::initTestCase()
{
    qttestutil::database::DatabaseUtil database ( DATABASEDRIVER );
    database.open ( DATABASE );
    database.read ( SQLTESTFILE );
}

void SaldoModelTest::testModel()
{
    ClubFrontend::Model::SaldoModel saldoModel ( QSqlDatabase::database(), 1025 );

    using ClubFrontend::Model::SaldoTable;
    const QSqlTableModel* model = saldoModel.findChild<QSqlTableModel* > ( SaldoTable::TABLENAME );
    QVERIFY ( model );
    QCOMPARE ( model->rowCount(), 2 );
    QSqlRecord record = model->record ( 0 );
    QCOMPARE ( record.value ( SaldoTable::bezeichnung ).toString(), QString ( "Start Saldo" ) );
    QCOMPARE ( record.value ( SaldoTable::betrag ).toString(), QString ( "0" ) );
}

void SaldoModelTest::testAmount()
{
    ClubFrontend::Model::SaldoModel saldoModel ( QSqlDatabase::database(), 1025 );

    float sum = saldoModel.amount();
    float expected = -15;
    QCOMPARE ( sum, expected );
}

}
}

QTEST_MAIN ( ClubFrontendTest::Model::SaldoModelTest )
#include "saldomodeltest.moc"
