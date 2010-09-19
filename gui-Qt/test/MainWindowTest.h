#ifndef MAINWINDOWTEST_H
#define MAINWINDOWTEST_H

#include <QObject>
#include <QtTest/QtTest>

#include "MemberModel.h"

namespace ClubFrontendTest
{

class MainWindowTest: public QObject
{
Q_OBJECT

private slots:
	void init();

	void testNewMember();
	void testMemberView();
	void testDeletedMemberView();

};

}

#endif
