/*
 * MemberModelTest.cpp
 *
 *  Created on: Mar 23, 2010
 *      Author: joerg
 */

#include "MemberModelTest.h"
#include "TestData.h"

#include "MemberModel.h"
#include "MemberDetailModel.h"

namespace ClubFrontendTest {

void MemberModelTest::initTestCase() {
	TestData testData;
	testData.createFakeMemberTable();
}

void MemberModelTest::testGetLastError() {
	ClubFrontend::MemberModel dataSource(QSqlDatabase::database());
	// Fehler Produzieren ? QCOMPARE(dataSource.getLastError(),QString());
}

void MemberModelTest::testGetMemberModel() {
	ClubFrontend::MemberModel dataSource(QSqlDatabase::database());

	const QSqlTableModel* model = dataSource.getMemberTableModel();
	QCOMPARE(model->rowCount(), 1);
	QSqlRecord record = model->record(0);
	QCOMPARE(record.value("name").toString(), QString("Kirk"));
}

}
