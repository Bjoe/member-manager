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

MemberDetailModel::MemberDetailModel(const QSqlDatabase& aDb)
{
	addressModel = getTableModel(AddressTable::TABLENAME, aDb);
	bankAccountModel = getTableModel(BankAccountTable::TABLENAME, aDb);
	contributionModel = getTableModel(ContributionTable::TABLENAME, aDb);
	ressourcenModel = getTableModel(RessourcenTable::TABLENAME, aDb);
	memberModel = getTableModel(MemberTable::TABLENAME, aDb);
}

MemberDetailModel::~MemberDetailModel()
{
	addressModel->~QSqlTableModel();
	bankAccountModel->~QSqlTableModel();
	contributionModel->~QSqlTableModel();
	ressourcenModel->~QSqlTableModel();
	memberModel->~QSqlTableModel();
}

QString MemberDetailModel::getLastError() const {
	// TODO besser model->lastError()
	QSqlDatabase db = QSqlDatabase::database();
	return db.lastError().text();
}

void MemberDetailModel::setMemberId(int id) {
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

int MemberDetailModel::newMember() {
	// Dirty Hack um ein Neues Mitglied einzutragen. Refactor!

	QVariant variant;
	variant.setValue(QString(""));

	int row = insertNewMember(memberModel, MemberTable::Name, variant);
	QSqlRecord record = memberModel->record(row);
	QVariant valueId = record.value(MemberTable::MemberId);

	insertNewMember(addressModel, AddressTable::MemberId, valueId);
	insertNewMember(bankAccountModel, BankAccountTable::MemberId, valueId);
	insertNewMember(contributionModel, ContributionTable::MemberId, valueId);
	insertNewMember(ressourcenModel, RessourcenTable::MemberId, valueId);

	return valueId.toInt();
}

int MemberDetailModel::insertNewMember(
		QSqlTableModel* aModel, const int& aColumnId, const QVariant& aValue) {
	QSqlRecord record = aModel->record();
	record.setValue(aColumnId, aValue);
	int row = aModel->rowCount();
	aModel->insertRow(row);
	aModel->setRecord(row, record);
	aModel->submitAll();
	return row;
}

QSqlTableModel* MemberDetailModel::getAddressTableModel() {
	return addressModel;
}

QSqlTableModel* MemberDetailModel::getBankAccountTableModel() {
	return bankAccountModel;
}

QSqlTableModel* MemberDetailModel::getContributionTableModel() {
	return contributionModel;
}

QSqlTableModel* MemberDetailModel::getRessourcenTableModel() {
	return ressourcenModel;
}

QSqlTableModel* MemberDetailModel::getMemberTableModel() {
	return memberModel;
}

QSqlTableModel* MemberDetailModel::getTableModel(const QString& aTableName, const QSqlDatabase& aDb) {
	QSqlTableModel* model = new QSqlTableModel(this, aDb);
	model->setTable(aTableName);
	model->select();
	return model;
}

}
