/*
 * KassaModelTest.cpp
 *
 *  Created on: Oct 3, 2010
 *      Author: joerg
 */

#include "KassaModelTest.h"

#include "KassaModel.h"

#include "TestData.h"
#include "DatabaseStructure.h"

#include <QSqlTableModel>
#include <QSqlRecord>
#include <QString>

namespace ClubFrontendTest
{

void KassaModelTest::initTestCase()
{
	TestData testData;
	testData.createFakeKassaTable();
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
