#include "MemberModelTest.h"

#include "MemberModel.h"

#include "TestData.h"
#include "MemberDetailModel.h"

#include <QSqlTableModel>
#include <QSqlRecord>
#include <QModelIndex>
#include <QVariant>
#include <QString>

namespace ClubFrontendTest
{

void MemberModelTest::initTestCase()
{
	TestData testData;
	testData.createFakeMemberTable();
}

void MemberModelTest::testGetLastError()
{
	ClubFrontend::MemberModel dataSource(QSqlDatabase::database());
	// Fehler Produzieren ? QCOMPARE(memberModel.getLastError(),QString());
}

void MemberModelTest::testGetMemberModel()
{
	ClubFrontend::MemberModel dataSource(QSqlDatabase::database());

	const QSqlTableModel* model = dataSource.getMemberTableModel();
	QCOMPARE(model->rowCount(), 2);
	QSqlRecord record = model->record(1);
	QCOMPARE(record.value("name").toString(), QString("Spock"));
}

void MemberModelTest::testSetFilter()
{
	ClubFrontend::MemberModel memberModel(QSqlDatabase::database());

	memberModel.setFilter("deleted='false'");

	const QSqlTableModel* model = memberModel.getMemberTableModel();
	QCOMPARE(model->rowCount(), 1);
	QSqlRecord record = model->record(0);
	QCOMPARE(record.value("name").toString(), QString("Kirk"));
}

void MemberModelTest::testGetMemberId()
{
	ClubFrontend::MemberModel memberModel(QSqlDatabase::database());

	const QSqlTableModel* model = memberModel.getMemberTableModel();

	const QModelIndex index = model->index(0,5);

	const int id = memberModel.getMemberId(index);

	QCOMPARE(id, 1025);
}

}
