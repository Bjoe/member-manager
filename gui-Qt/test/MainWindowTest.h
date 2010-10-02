#ifndef MAINWINDOWTEST_H
#define MAINWINDOWTEST_H

#include <QObject>
#include <QtTest/QtTest>

#include "MemberModel.h"
#include "Executor.h"

namespace ClubFrontendTest
{

class MainWindowTest: public QObject, public Executor
{
Q_OBJECT

public:
	virtual void doWork();

private slots:
	void init();

	void testNewMember();
	void testEditMember();
	void testMemberView();
	void testDeletedMemberView();

private:
	QString id;
};

}

#endif
