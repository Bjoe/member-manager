#include "MemberModelTest.h"
#include "KassaModelTest.h"
#include "MemberDetailModelTest.h"
#include "MemberFilterTest.h"
#include "MemberDialogTest.h"
#include "MainWindowTest.h"
#include "ConnectionDialogTest.h"
#include "TestData.h"

#include <QtTest/QtTest>

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName("dorfverw.dat");
	if (!db.open())
	{
		qDebug() << db.lastError().text();
		return 1;
	}

	ClubFrontendTest::MemberModelTest sourceTest;
	QTest::qExec(&sourceTest);

	ClubFrontendTest::MemberFilterTest filterTest;
	QTest::qExec(&filterTest);

	ClubFrontendTest::MainWindowTest mainWindowTest;
	QTest::qExec(&mainWindowTest);

	ClubFrontendTest::MemberDialogTest dialogTest;
	QTest::qExec(&dialogTest);

	ClubFrontendTest::MemberDetailModelTest memberDialogTest;
	QTest::qExec(&memberDialogTest);

	ClubFrontendTest::ConnectionDialogTest connectionDialogTest;
	QTest::qExec(&connectionDialogTest);

	ClubFrontendTest::KassaModelTest kassaModelTest;
	QTest::qExec(&kassaModelTest);

	return 0;
}
