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

MemberModel::MemberModel(const QSqlDatabase& aDb) :
		model(new QSqlTableModel(this, aDb))
{
	model->setTable(MemberTable::TABLENAME);
	model->select();
}

MemberModel::~MemberModel()
{
	delete model;
}

QString MemberModel::getLastError() const
{
	return model->lastError().text();
}

QSqlTableModel* MemberModel::getMemberTableModel() const
{
	return model;
}

}
