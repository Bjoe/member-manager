/*
 * MemberDetailModel.cpp
 *
 *  Created on: Jul 17, 2010
 *      Author: joerg
 */

#include "MemberDetailModel.h"
#include "DatabaseStructure.h"

namespace ClubFrontend
{

MemberDetailModel::MemberDetailModel(const QSqlDatabase& aDb) :
	addressModel(new QSqlTableModel(this, aDb)), bankAccountModel(
			new QSqlTableModel(this, aDb)), contributionModel(
			new QSqlTableModel(this, aDb)), ressourcenModel(new QSqlTableModel(
			this, aDb)), memberModel(new QSqlTableModel(this, aDb)), id(0)
{
	setTableModel(AddressTable::TABLENAME, addressModel);
	setTableModel(BankAccountTable::TABLENAME, bankAccountModel);
	setTableModel(ContributionTable::TABLENAME, contributionModel);
	setTableModel(RessourcenTable::TABLENAME, ressourcenModel);
	setTableModel(MemberTable::TABLENAME, memberModel);
}

MemberDetailModel::~MemberDetailModel()
{
	delete addressModel;
	delete bankAccountModel;
	delete contributionModel;
	delete ressourcenModel;
	delete memberModel;
}

QSqlTableModel* MemberDetailModel::setTableModel(const QString& aTableName,
		QSqlTableModel* const aModel)
{
	aModel->setTable(aTableName);
	aModel->select();
}

QString MemberDetailModel::getLastError() const
{
	// TODO besser model->lastError()
	QSqlDatabase db = QSqlDatabase::database();
	return db.lastError().text();
}

void MemberDetailModel::setMemberId(int anId)
{
	id = anId;

	QString pkey = MemberTable::COLUMNNAME[MemberTable::MemberId];
	QString filter = QString(pkey + " = %1").arg(id);
	addressModel->setFilter(filter);
	addressModel->select();
	bankAccountModel->setFilter(filter);
	bankAccountModel->select();
	contributionModel->setFilter(filter);
	contributionModel->select();
	ressourcenModel->setFilter(filter);
	ressourcenModel->select();
	memberModel->setFilter(filter);
	memberModel->select();
}

int MemberDetailModel::getMemberId() const
{
	return id;
}

int MemberDetailModel::newMember()
{
	// Dirty Hack um ein Neues Mitglied einzutragen.
	QVariant variant(true);
	int row = insertNewMember(memberModel, MemberTable::Deleted, variant);
	QSqlRecord record = memberModel->record(row);
	QVariant valueId = record.value(MemberTable::MemberId);

	insertNewMember(addressModel, AddressTable::MemberId, valueId);
	insertNewMember(bankAccountModel, BankAccountTable::MemberId, valueId);
	insertNewMember(contributionModel, ContributionTable::MemberId, valueId);
	insertNewMember(ressourcenModel, RessourcenTable::MemberId, valueId);

	int newId = valueId.toInt();
	setMemberId(newId);
	return newId;
}

int MemberDetailModel::insertNewMember(QSqlTableModel* aModel,
		const int& aColumnId, const QVariant& aValue)
{
	QSqlRecord record = aModel->record();
	record.setValue(aColumnId, aValue);
	int row = aModel->rowCount();
	aModel->insertRow(row);
	aModel->setRecord(row, record);
	aModel->submitAll();
	return row;
}

void MemberDetailModel::deleteMember()
{
	if (id == 0)
		return;

	const QString whereClause = QString(" where %1=%2").arg(
			MemberTable::COLUMNNAME[MemberTable::MemberId]).arg(id);
	const QString columnDeteled = MemberTable::COLUMNNAME[MemberTable::Deleted];

	QSqlQuery query("select * from " + MemberTable::TABLENAME + whereClause
			+ " AND " + columnDeteled + "='false'");
	if (query.next())
	{
		query .exec("update " + MemberTable::TABLENAME + " set "
				+ columnDeteled + "='true' " + whereClause + " AND "
				+ columnDeteled + "='false'");
	}
	else
	{
		query.exec("delete from " + MemberTable::TABLENAME + whereClause);
		query.exec("delete from " + AddressTable::TABLENAME + whereClause);
		query.exec("delete from " + BankAccountTable::TABLENAME + whereClause);
		query.exec("delete from " + ContributionTable::TABLENAME + whereClause
				+ " AND " + ContributionTable::COLUMNNAME[ContributionTable::Fee] + " isNull AND " +
				ContributionTable::COLUMNNAME[ContributionTable::Donation] + " isNull AND " +
				ContributionTable::COLUMNNAME[ContributionTable::ValidFrom] + " isNull AND" +
				ContributionTable::COLUMNNAME[ContributionTable::Info] + " isNull");
		query.exec("delete from " + RessourcenTable::TABLENAME + whereClause);
	}
}

QSqlTableModel* MemberDetailModel::getAddressTableModel() const
{
	return addressModel;
}

QSqlTableModel* MemberDetailModel::getBankAccountTableModel() const
{
	return bankAccountModel;
}

QSqlTableModel* MemberDetailModel::getContributionTableModel() const
{
	return contributionModel;
}

QSqlTableModel* MemberDetailModel::getRessourcenTableModel() const
{
	return ressourcenModel;
}

QSqlTableModel* MemberDetailModel::getMemberTableModel() const
{
	return memberModel;
}

}
