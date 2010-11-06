/*
 * MemberModel.cpp
 *
 *  Created on: Mar 23, 2010
 *      Author: joerg
 */
#include "MemberModel.h"

#include <QSqlRecord>

#include "DatabaseStructure.h"

namespace ClubFrontend
{

MemberModel::MemberModel(const QSqlDatabase& aDb) :
		model(new QSqlTableModel(this, aDb))
{
	model->setTable(MemberTable::TABLENAME);
	model->setHeaderData(MemberTable::MemberId, Qt::Horizontal, tr("Nr."));
	model->setHeaderData(MemberTable::FirstName, Qt::Horizontal, tr("Vorname"));
	model->setHeaderData(MemberTable::Name, Qt::Horizontal, tr("Name"));
	model->setHeaderData(MemberTable::NickName, Qt::Horizontal, tr("Nickname"));
	model->setHeaderData(MemberTable::EntryDate, Qt::Horizontal, tr("Eintritts Datum"));
	model->setHeaderData(MemberTable::Info, Qt::Horizontal, tr("Info"));
	refresh();
}

MemberModel::~MemberModel()
{
	delete model;
}

void MemberModel::setFilter(const QString aSqlFilter)
{
	model->setFilter(aSqlFilter);
	refresh();
}

void MemberModel::refresh()
{
	model->select();
}

int MemberModel::getMemberId(const QModelIndex& anIndex)
{
	QSqlRecord record = model->record(anIndex.row());
	return record.value(MemberTable::MemberId).toInt();
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
