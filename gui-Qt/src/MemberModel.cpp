/*
 * MemberModel.cpp
 *
 *  Created on: Mar 23, 2010
 *      Author: joerg
 */
#include "MemberModel.h"
#include "DatabaseStructure.h"

namespace ClubFrontend
{

MemberModel::~MemberModel()
{
	memberModel->~QSqlTableModel();
}

MemberModel::MemberModel(const QSqlDatabase & aDb)
{
	memberModel = getTableModel("dorfmitglied", aDb);
}

QString MemberModel::getLastError() const
{
	QSqlDatabase db = QSqlDatabase::database();
	return db.lastError().text();
}

QSqlTableModel* MemberModel::getMemberTableModel()
{
	return memberModel;
}

QSqlTableModel* MemberModel::getTableModel(const QString& aTableName,
		const QSqlDatabase& aDb)
{
	QSqlTableModel* model = new QSqlTableModel(this, aDb);
	model->setTable(aTableName);
	model->select();
	return model;
}

}
