#ifndef MEMBERDIALOGTEST_H
#define MEMBERDIALOGTEST_H

#include <QObject>
#include <QtTest/QtTest>

namespace ClubFrontendTest
{

class MemberDialogTest: public QObject
{
Q_OBJECT

private slots:
	void initTestCase();
	void showMember();
	void newMember();
	void changeMember();
};

}

#endif // MEMBERDIALOGTEST_H
