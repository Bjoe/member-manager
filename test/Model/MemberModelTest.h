/*
 * MemberModelTest.h
 *
 *  Created on: Mar 23, 2010
 *      Author: joerg
 */

#ifndef MEMBERMODELTEST_H_
#define MEMBERMODELTEST_H_

#include <QtTest/QtTest>

namespace ClubFrontendTest
{

class MemberModelTest: public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testGetLastError();
    void testGetMemberModel();
    void testSetFilter();
    void testGetMemberId();
    void testGetSelectedMembers();
};

}

#endif /* MEMBERMODELTEST_H_ */
