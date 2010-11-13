/*
 * SaldoModel.h
 *
 *  Created on: Oct 9, 2010
 *      Author: joerg
 */

#ifndef SALDOMODEL_H_
#define SALDOMODEL_H_

#include <QtCore>
#include <QSqlDatabase>
#include <QSqlTableModel>

namespace ClubFrontend
{

class SaldoModel: public QObject
{
public:
	SaldoModel(const QSqlDatabase& aDb, const int aMemberId);
	virtual ~SaldoModel();

	void setMemberId(const int aMemberId);
	int amount() const;
	void refresh();

	QSqlTableModel* getSaldoTableModel() const;

private:
	QSqlTableModel* model;
};

}

#endif /* SALDOMODEL_H_ */
