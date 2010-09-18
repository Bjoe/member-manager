/*
 * MemberModel.h
 *
 *  Created on: Mar 23, 2010
 *      Author: joerg
 */

#ifndef MEMBERMODEL_H_
#define MEMBERMODEL_H_

#include <QtCore>
#include <QtSql>
#include "MemberDetailModel.h"

namespace ClubFrontend
{

class MemberModel: public QObject
{

public:
	virtual ~MemberModel();
	MemberModel(const QSqlDatabase& aDb);

	QString getLastError() const;
	QSqlTableModel* getMemberTableModel();

private:
	QSqlTableModel* getTableModel(const QString& aTableName,
			const QSqlDatabase& aDb);

	QSqlTableModel* memberModel;
};

}

#endif /* MEMBERMODEL_H_ */
