#include "MemberDetailModelTest.h"

#include "MemberDetailModel.h"

#include "TestData.h"
#include "DatabaseStructure.h"

#include <QDebug>
#include <QSqlRecord>

namespace ClubFrontendTest
{

void MemberDetailModelTest::initTestCase()
{
	TestData testData;
	testData.createFakeMemberTable();
	testData.createFakeAdressTable();
	testData.createFakeBankTable();
	testData.createFakeContributionTable();
	testData.createFakeRessourcenTable();
}

void MemberDetailModelTest::testGetLastError()
{
	// XXX Test fehlt noch
	// keine Aenderung und dann model->submit()
}

void MemberDetailModelTest::testGetAddressModel()
{
	ClubFrontend::MemberDetailModel dataSource(QSqlDatabase::database());

	const QSqlTableModel* model = dataSource.getAddressTableModel();
	QCOMPARE(model->rowCount(), 2);
	QSqlRecord record = model->record(0);
	QCOMPARE(record.value("ort").toString(), QString("Bloedeldorff"));
}

void MemberDetailModelTest::testGetBankAccountModel()
{
	ClubFrontend::MemberDetailModel dataSource(QSqlDatabase::database());

	const QSqlTableModel* model = dataSource.getBankAccountTableModel();
	QCOMPARE(model->rowCount(), 1);
	QSqlRecord record = model->record(0);
	QCOMPARE(record.value("bank").toString(), QString("sparstrumpf"));
}

void MemberDetailModelTest::testGetContributionModel()
{
	ClubFrontend::MemberDetailModel dataSource(QSqlDatabase::database());

	const QSqlTableModel* model = dataSource.getContributionTableModel();
	QCOMPARE(model->rowCount(), 1);
	QSqlRecord record = model->record(0);
	double fee = 15.00;
	QCOMPARE(record.value("beitrag").toDouble(), fee);
}

void MemberDetailModelTest::testGetRessourcenModel()
{
	ClubFrontend::MemberDetailModel dataSource(QSqlDatabase::database());

	const QSqlTableModel* model = dataSource.getRessourcenTableModel();
	QCOMPARE(model->rowCount(), 1);
	QSqlRecord record = model->record(0);
	QCOMPARE(record.value("email").toString(), QString("fooo@baaar.xx"));
}

void MemberDetailModelTest::testGetMemberModel()
{
	ClubFrontend::MemberDetailModel memberModel(QSqlDatabase::database());

	const QSqlTableModel* model = memberModel.getMemberTableModel();
	QCOMPARE(model->rowCount(), 2);
	QSqlRecord record = model->record(0);
	QCOMPARE(record.value("name").toString(), QString("Kirk"));
}

void MemberDetailModelTest::testSetMemberId()
{
	ClubFrontend::MemberDetailModel dataSource(QSqlDatabase::database());

	const QSqlTableModel* ressourcenModel =
			dataSource.getRessourcenTableModel();
	const QSqlTableModel* addressModel = dataSource.getAddressTableModel();
	const QSqlTableModel* contributionModel =
			dataSource.getContributionTableModel();
	const QSqlTableModel* accountModel = dataSource.getBankAccountTableModel();
	const QSqlTableModel* memberModel = dataSource.getMemberTableModel();

	dataSource.setMemberId(1025);

	QCOMPARE(memberModel->rowCount(), 1);
	QSqlRecord record = memberModel->record(0);
	QCOMPARE(record.value("name").toString(), QString("Kirk"));

	QCOMPARE(addressModel->rowCount(), 1);
	record = addressModel->record(0);
	QCOMPARE(record.value("ort").toString(), QString("Bloedeldorf"));

	QCOMPARE(accountModel->rowCount(), 1);
	record = accountModel->record(0);
	QCOMPARE(record.value("bank").toString(), QString("sparstrumpf"));

	QCOMPARE(contributionModel->rowCount(), 1);
	record = contributionModel->record(0);
	double fee = 15.00;
	QCOMPARE(record.value("beitrag").toDouble(), fee);

	QCOMPARE(ressourcenModel->rowCount(), 1);
	record = ressourcenModel->record(0);
	QCOMPARE(record.value("email").toString(), QString("fooo@baaar.xx"));

	QCOMPARE(dataSource.getMemberId(), 1025);
}

void MemberDetailModelTest::testNewMember()
{
	ClubFrontend::MemberDetailModel memberDetailModel(QSqlDatabase::database());
	int id = memberDetailModel.newMember();

	QCOMPARE(getMemberId(memberDetailModel.getMemberTableModel(),
					ClubFrontend::MemberTable::MemberId), id);
	QCOMPARE(getMemberId(memberDetailModel.getAddressTableModel(),
					ClubFrontend::AddressTable::MemberId), id);
	QCOMPARE(getMemberId(memberDetailModel.getBankAccountTableModel(),
					ClubFrontend::BankAccountTable::MemberId), id);
	QCOMPARE(getMemberId(memberDetailModel.getContributionTableModel(),
					ClubFrontend::ContributionTable::MemberId), id);
	QCOMPARE(getMemberId(memberDetailModel.getRessourcenTableModel(),
					ClubFrontend::RessourcenTable::MemberId), id);
}

void MemberDetailModelTest::testDeleteMember()
{
	ClubFrontend::MemberDetailModel memberDetailModel(QSqlDatabase::database());
	int id = memberDetailModel.newMember();

	memberDetailModel.deleteMember();

	const QString whereClause = QString(" where dorfmitglied_pkey=%1").arg(id);

	using ClubFrontend::MemberTable;
	QSqlQuery query;
	query.exec("select * from " + MemberTable::TABLENAME + whereClause);
	QVERIFY(!query.next());


}

int MemberDetailModelTest::getMemberId(const QSqlTableModel* aModel,
		const int& aColumnId)
{
	QSqlRecord record = aModel->record(0);
	return record.value(aColumnId).toInt();
}

}
