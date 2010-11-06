/*
 * SaldoModel.cpp
 *
 *  Created on: Oct 9, 2010
 *      Author: joerg
 */

#include "SaldoModel.h"

#include "DatabaseStructure.h"

#include <QString>

namespace ClubFrontend
{

SaldoModel::SaldoModel(const QSqlDatabase& aDb, const int aMemberId) :
		model(new QSqlTableModel(this, aDb))
{
	model->setTable(SaldoTable::TABLENAME);
	setMemberId(aMemberId);
	refresh();
}

SaldoModel::~SaldoModel()
{
}

void SaldoModel::setMemberId(const int aMemberId)
{
	QString columnname = SaldoTable::COLUMNNAME[SaldoTable::dorfmitglied_pkey];
	QString filter = QString(columnname + " = %1").arg(aMemberId);
	model->setFilter(filter);
}

void SaldoModel::refresh()
{
	model->select();
}

QSqlTableModel* SaldoModel::getSaldoTableModel() const
{
	return model;
}

}
