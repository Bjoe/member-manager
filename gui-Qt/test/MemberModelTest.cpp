#include "MemberModelTest.h"

#include "MemberModel.h"

#include "TestData.h"
#include "MemberDetailModel.h"

#include <QSqlTableModel>
#include <QSqlRecord>
#include <QVariant>
#include <QString>

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
