/*
 * KassaModel.cpp
 *
 *  Created on: Oct 3, 2010
 *      Author: joerg
 */

#include "KassaModel.h"

#include "DatabaseStructure.h"

namespace ClubFrontend
{

KassaModel::KassaModel(const QSqlDatabase& aDb) :
	model(new QSqlTableModel(this, aDb))
{
	model->setTable(KassaTable::TABLENAME);
	setDefaultFilter();
	refresh();
}

KassaModel::~KassaModel()
{
	delete model;
}

void KassaModel::setDefaultFilter()
{
	model->setFilter(KassaTable::COLUMNNAME[KassaTable::deleted] + "='false'");
}

void KassaModel::refresh()
{
	model->select();
}

QSqlTableModel* KassaModel::getKassaTableModel() const
{
	return model;
}

}
