#ifndef MEMBERDIALOGTEST_H
#define MEMBERDIALOGTEST_H

#include <QObject>
#include <QtTest/QtTest>

#include "MemberDialog.h"

namespace ClubFrontendTest
{

class MemberDialogTest : public QObject
{
	Q_OBJECT

private slots:
	void setMemberId();
	void newMember();
	void changeMember();

	void foo();
};

}

#endif // MEMBERDIALOGTEST_H
