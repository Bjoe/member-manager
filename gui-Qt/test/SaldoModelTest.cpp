/*
 * SaldoModelTest.cpp
 *
 *  Created on: Oct 9, 2010
 *      Author: joerg
 */

#include "SaldoModelTest.h"

#include "SaldoModel.h"

#include "TestData.h"
#include "DatabaseStructure.h"

#include <QSqlTableModel>
#include <QSqlRecord>
#include <QString>

namespace ClubFrontendTest
{

void SaldoModelTest::initTestCase()
{
	TestData testData;
	testData.createFakeBalanceTable();
}

void SaldoModelTest::testModel()
{
	ClubFrontend::SaldoModel saldoModel(QSqlDatabase::database(), 1025);

	const QSqlTableModel* model = saldoModel.getSaldoTableModel();
	QCOMPARE(model->rowCount(), 2);
	QSqlRecord record = model->record(0);
	using ClubFrontend::SaldoTable;
	QCOMPARE(record.value(SaldoTable::bezeichnung).toString(), QString("Start Saldo"));
	QCOMPARE(record.value(SaldoTable::betrag).toString(), QString("0"));
}

}
