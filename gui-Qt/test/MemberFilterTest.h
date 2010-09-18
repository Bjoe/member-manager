/*
 * MemberFilterTest.h
 *
 *  Created on: Jul 6, 2010
 *      Author: joerg
 */

#ifndef MEMBERFILTERTEST_H_
#define MEMBERFILTERTEST_H_

#include <QObject>
#include <QtTest/QtTest>

namespace ClubFrontendTest
{

class MemberFilterTest: public QObject
{
Q_OBJECT

private slots:
	void testSetDeleted();
	void testSetDeletedFalse();
};

}

#endif /* MEMBERFILTERTEST_H_ */
