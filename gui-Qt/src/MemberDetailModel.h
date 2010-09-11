/*
 * MemberDetailModel.h
 *
 *  Created on: Jul 17, 2010
 *      Author: joerg
 */

#ifndef MEMBERDETAILMODEL_H_
#define MEMBERDETAILMODEL_H_

#include <QtCore>
#include <QtSql>

namespace ClubFrontend
{

class MemberDetailModel : public QObject
{
public:
	MemberDetailModel(const QSqlDatabase& aDb);
	virtual ~MemberDetailModel();

	QString getLastError() const;

	void setMemberId(int id);
	int newMember();

	QSqlTableModel* getAddressTableModel();
	QSqlTableModel* getBankAccountTableModel();
	QSqlTableModel* getContributionTableModel();
	QSqlTableModel* getRessourcenTableModel();
	QSqlTableModel* getMemberTableModel();

private:
	int insertNewMember(QSqlTableModel* aModel, const int& aColumnId, const QVariant& aValue);
	QSqlTableModel* getTableModel(const QString& aTableName, const QSqlDatabase& aDb);

	QSqlTableModel* addressModel;
	QSqlTableModel* bankAccountModel;
	QSqlTableModel* contributionModel;
	QSqlTableModel* ressourcenModel;
	QSqlTableModel* memberModel;
};

}

#endif /* MEMBERDETAILMODEL_H_ */
