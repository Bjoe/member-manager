/*
 * MemberModel.h
 *
 *  Created on: Mar 23, 2010
 *      Author: joerg
 */

#ifndef MEMBERMODEL_H_
#define MEMBERMODEL_H_

#include <QtCore>
#include <QSqlDatabase>
#include <QSqlTableModel>

#include "MemberDetailModel.h"

namespace ClubFrontend
{

class MemberModel: public QObject
{

public:
	MemberModel(const QSqlDatabase& aDb);
	virtual ~MemberModel();

	void setFilter(const QString aSqlFilter);
	void refresh();

	QString getLastError() const;
	QSqlTableModel* getMemberTableModel() const;

private:

	QSqlTableModel* const model;
};

}

#endif /* MEMBERMODEL_H_ */
