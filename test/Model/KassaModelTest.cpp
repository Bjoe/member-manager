/*
 * KassaModelTest.cpp
 *
 *  Created on: Oct 3, 2010
 *      Author: joerg
 */

#include "KassaModelTest.h"

#include "Model/KassaModel.h"

#include "TestConfig.h"
#include "TestUtils/DatabaseUtils.h"
#include "Model/DatabaseStructure.h"

#include <QSqlTableModel>
#include <QSqlRecord>
#include <QString>

namespace ClubFrontendTest
{
namespace Model
{

void KassaModelTest::initTestCase()
{
    Utils::DatabaseUtils database ( DATABASEDRIVER );
    database.open ( DATABASE );
    database.read ( SQLTESTFILE );
}

void KassaModelTest::testModel()
{
    ClubFrontend::Model::KassaModel kassaModel ( QSqlDatabase::database() );

    const QSqlTableModel* model = kassaModel.findChild<QSqlTableModel* > ( "model" );
    QVERIFY ( model );
    QCOMPARE ( model->rowCount(), 3 );
    QSqlRecord record = model->record ( 1 );
    using ClubFrontend::Model::KassaTable;
    QCOMPARE ( record.value ( KassaTable::betrag ).toString(), QString ( "104.86" ) );
}

}
}

QTEST_MAIN ( ClubFrontendTest::Model::KassaModelTest )
#include "KassaModelTest.moc"
