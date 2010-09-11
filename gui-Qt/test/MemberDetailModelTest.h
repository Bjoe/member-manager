/*
 * MemberDetailModelTest.h
 *
 *  Created on: Jul 17, 2010
 *      Author: joerg
 */

#ifndef MEMBERDETAILMODELTEST_H_
#define MEMBERDETAILMODELTEST_H_

#include <QObject>
#include <QtTest/QtTest>
#include <QSqlTableModel>

namespace ClubFrontendTest
{

class MemberDetailModelTest : public QObject
{	Q_OBJECT

private slots:
	void initTestCase();
	void testGetLastError();
	void testGetAddressModel();
	void testGetBankAccountModel();
	void testGetContributionModel();
	void testGetRessourcenModel();
	void testGetMemberModel();
	void testSetMemberId();
	void testNewMember();

private:
	int getMemberId(const QSqlTableModel* aModel, const int& aColumnId);
};

}

#endif /* MEMBERDETAILMODELTEST_H_ */
