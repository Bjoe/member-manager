/*
 * SaldoModel.cpp
 *
 *  Created on: Oct 9, 2010
 *      Author: joerg
 */

#include "SaldoModel.h"

#include "DatabaseStructure.h"

#include <QSqlRecord>
#include <QSqlQuery>
#include <QString>
#include <QVariant>

namespace ClubFrontend
{

SaldoModel::SaldoModel(const QSqlDatabase& aDb, const int aMemberId) :
		model(new QSqlTableModel(this, aDb))
{
	model->setTable(SaldoTable::TABLENAME);
	model->setHeaderData(SaldoTable::betrag, Qt::Horizontal, tr("Betrag"));
	model->setHeaderData(SaldoTable::datum, Qt::Horizontal, tr("Valuta Datum"));
	model->setHeaderData(SaldoTable::bezeichnung, Qt::Horizontal, tr("Bezeichnung"));
	model->setHeaderData(SaldoTable::barkonto, Qt::Horizontal, tr("Barkonto"));
	model->setHeaderData(SaldoTable::konten, Qt::Horizontal, tr("Konten"));
	model->setHeaderData(SaldoTable::kasse_pkey, Qt::Horizontal, tr("Kassa Id"));
	model->setHeaderData(SaldoTable::info, Qt::Horizontal, tr("Info"));
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

int SaldoModel::amount() const
{
  QSqlRecord record = model->record(0);
  QVariant id = record.value(SaldoTable::dorfmitglied_pkey);
  QString query = QString("SELECT SUM(betrag) FROM saldo WHERE dorfmitglied_pkey=%1").arg(id.toString());
  QSqlQuery sqlQuery(query);
  sqlQuery.next();
  QVariant sum = sqlQuery.value(0);
  return sum.toInt();
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
