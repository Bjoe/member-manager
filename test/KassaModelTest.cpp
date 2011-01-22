/*
 * KassaModelTest.cpp
 *
 *  Created on: Oct 3, 2010
 *      Author: joerg
 */

#include "KassaModelTest.h"

#include "KassaModel.h"

#include "TestConfig.h"
#include "DatabaseUtils.h"
#include "DatabaseStructure.h"

#include <QSqlTableModel>
#include <QSqlRecord>
#include <QString>

namespace ClubFrontendTest
{

void KassaModelTest::initTestCase()
{
    Utils::DatabaseUtils database(DATABASEDRIVER);
    database.open(DATABASE);
    database.read(SQLTESTFILE);
}

void KassaModelTest::testModel()
{
	ClubFrontend::KassaModel kassaModel(QSqlDatabase::database());

	const QSqlTableModel* model = kassaModel.getKassaTableModel();
	QCOMPARE(model->rowCount(), 3);
	QSqlRecord record = model->record(1);
	using ClubFrontend::KassaTable;
	QCOMPARE(record.value(KassaTable::betrag).toString(), QString("104.86"));
}

}

QTEST_MAIN(ClubFrontendTest::KassaModelTest)
#include "KassaModelTest.moc"
