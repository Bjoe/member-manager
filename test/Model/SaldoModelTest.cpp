/*
 * SaldoModelTest.cpp
 *
 *  Created on: Oct 9, 2010
 *      Author: joerg
 */

#include "SaldoModelTest.h"

#include "Model/SaldoModel.h"

#include "TestConfig.h"
#include "TestUtils/DatabaseUtils.h"
#include "Model/DatabaseStructure.h"

#include <QSqlTableModel>
#include <QSqlRecord>
#include <QString>

namespace ClubFrontendTest
{

void SaldoModelTest::initTestCase()
{
    Utils::DatabaseUtils database ( DATABASEDRIVER );
    database.open ( DATABASE );
    database.read ( SQLTESTFILE );
}

void SaldoModelTest::testModel()
{
    ClubFrontend::SaldoModel saldoModel ( QSqlDatabase::database(), 1025 );

    const QSqlTableModel* model = saldoModel.getSaldoTableModel();
    QCOMPARE ( model->rowCount(), 2 );
    QSqlRecord record = model->record ( 0 );
    using ClubFrontend::SaldoTable;
    QCOMPARE ( record.value ( SaldoTable::bezeichnung ).toString(), QString ( "Start Saldo" ) );
    QCOMPARE ( record.value ( SaldoTable::betrag ).toString(), QString ( "0" ) );
}

void SaldoModelTest::testAmount()
{
    ClubFrontend::SaldoModel saldoModel ( QSqlDatabase::database(), 1025 );

    float sum = saldoModel.amount();
    float expected = -15;
    QCOMPARE ( sum, expected );
}

}

QTEST_MAIN ( ClubFrontendTest::SaldoModelTest )
#include "SaldoModelTest.moc"
