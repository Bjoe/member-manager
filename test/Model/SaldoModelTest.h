/*
 * SaldoModelTest.h
 *
 *  Created on: Oct 9, 2010
 *      Author: joerg
 */

#ifndef SALDOMODELTEST_H_
#define SALDOMODELTEST_H_

#include <QtTest/QtTest>

namespace ClubFrontendTest
{

class SaldoModelTest: public QObject
{
Q_OBJECT

private slots:
	void initTestCase();
	void testModel();
	void testAmount();
};

}

#endif /* SALDOMODELTEST_H_ */
