/*
 * KassaModelTest.h
 *
 *  Created on: Oct 3, 2010
 *      Author: joerg
 */

#ifndef KASSAMODELTEST_H_
#define KASSAMODELTEST_H_

#include <QObject>
#include <QtTest/QtTest>

namespace ClubFrontendTest
{

class KassaModelTest: public QObject
{
	Q_OBJECT

private slots:
	void initTestCase();
	void testModel();
};

}

#endif /* KASSAMODELTEST_H_ */