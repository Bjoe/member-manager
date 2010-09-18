/*
 * ConnectionDialogTest.h
 *
 *  Created on: Aug 11, 2010
 *      Author: joerg
 */

#ifndef CONNECTIONDIALOGTEST_H_
#define CONNECTIONDIALOGTEST_H_

#include <QObject>
#include <QtTest/QtTest>

namespace ClubFrontendTest
{

class ConnectionDialogTest: public QObject
{
Q_OBJECT

private slots:
	void testGetUsername();
	void testGetPassword();
	void testGetDatebaseName();
	void testGetHostname();
	void testGetPort();
	void testGetDriverName();
	void testOkButton();
	void testCancelButton();
};

}

#endif /* CONNECTIONDIALOGTEST_H_ */
