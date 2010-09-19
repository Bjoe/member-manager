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

class MemberDetailModel: public QObject
{
public:
	MemberDetailModel(const QSqlDatabase& aDb = QSqlDatabase::database());
	virtual ~MemberDetailModel();

	QString getLastError() const;

	void setMemberId(int id);
	int getMemberId() const;
	int newMember();

	QSqlTableModel* getAddressTableModel() const;
	QSqlTableModel* getBankAccountTableModel() const;
	QSqlTableModel* getContributionTableModel() const;
	QSqlTableModel* getRessourcenTableModel() const;
	QSqlTableModel* getMemberTableModel() const;

private:
	int insertNewMember(QSqlTableModel* aModel, const int& aColumnId,
			const QVariant& aValue);
	QSqlTableModel* setTableModel(const QString& aTableName,
			QSqlTableModel* const aModel);

	QSqlTableModel* const addressModel;
	QSqlTableModel* const bankAccountModel;
	QSqlTableModel* const contributionModel;
	QSqlTableModel* const ressourcenModel;
	QSqlTableModel* const memberModel;
	int id;
};

}

#endif /* MEMBERDETAILMODEL_H_ */
