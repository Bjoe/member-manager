/*
 * SaldoModelTest.cpp
 *
 *  Created on: Oct 9, 2010
 *      Author: joerg
 */

#include "SaldoModelTest.h"

#include "Model/SaldoModel.h"

#include "TestConfig.h"
#include <DatabaseUtils.h>
#include "Model/DatabaseStructure.h"

#include <QSqlTableModel>
#include <QSqlRecord>
#include <QString>

namespace ClubFrontendTest
{
namespace Model
{

void SaldoModelTest::initTestCase()
{
    TestUtils::Database::DatabaseUtils database ( DATABASEDRIVER );
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
#include "SaldoModelTest.moc"
