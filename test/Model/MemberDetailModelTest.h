/*
 * MemberDetailModelTest.h
 *
 *  Created on: Jul 17, 2010
 *      Author: joerg
 */

#ifndef MEMBERDETAILMODELTEST_H_
#define MEMBERDETAILMODELTEST_H_

#include <QtTest/QtTest>
#include <QSqlTableModel>

namespace ClubFrontendTest
{
namespace Model
{
  
class MemberDetailModelTest: public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testGetAddressModel();
    void testGetBankAccountModel();
    void testGetContributionModel();
    void testGetRessourcenModel();
    void testGetMemberModel();
    void testGetMember();
    void testSetMemberId();
    void testNewMember();
    void testDeleteMember();

private:
    int getMemberId ( const QSqlTableModel* aModel, const int& aColumnId );
};

}
}

#endif /* MEMBERDETAILMODELTEST_H_ */
