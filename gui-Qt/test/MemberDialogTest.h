#ifndef MEMBERDIALOGTEST_H
#define MEMBERDIALOGTEST_H

#include <QObject>
#include <QtTest/QtTest>

#include "Executor.h"

namespace ClubFrontendTest
{

class MemberDialogTest: public QObject, public Executor
{
Q_OBJECT

public:
	virtual void doWork();

private slots:
	void initTestCase();
	void showMember();
	void newMember();
	void changeMember();
	void newMemberDiscard();
};

}

#endif // MEMBERDIALOGTEST_H
