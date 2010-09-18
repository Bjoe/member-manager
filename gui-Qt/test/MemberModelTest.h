/*
 * MemberModelTest.h
 *
 *  Created on: Mar 23, 2010
 *      Author: joerg
 */

#ifndef MEMBERMODELTEST_H_
#define MEMBERMODELTEST_H_

#include <QObject>
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
};

}

#endif /* MEMBERMODELTEST_H_ */
