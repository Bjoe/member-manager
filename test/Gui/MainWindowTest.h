#ifndef MAINWINDOWTEST_H
#define MAINWINDOWTEST_H

#include <QtTest/QtTest>

#include "TestUtils/Handler.h"

namespace ClubFrontendTest
{

class MainWindowTest: public QObject, public Handler
{
Q_OBJECT

public:
	virtual void handle();

private slots:
	void init();

	void testNewMember();
	void testEditMember();
	void testSelectedMember();
	void testMemberView();
	void testDeletedMemberView();
	void testShowKassaView();
	void testShowSaldo();
	void testCopyMailAdress();

private:
	QString id;
};

}

#endif
