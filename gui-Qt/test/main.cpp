#include "MemberModelTest.h"
#include "MemberDetailModelTest.h"
#include "MemberFilterTest.h"
#include "MemberDialogTest.h"
#include "MainWindowTest.h"

#include <QtTest/QtTest>

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName("dorfverw.dat");
	db.open();

	ClubFrontendTest::MemberModelTest sourceTest;
	QTest::qExec(&sourceTest);

	ClubFrontendTest::MemberDetailModelTest memberDialogTest;
	QTest::qExec(&memberDialogTest);

	ClubFrontendTest::MemberFilterTest filterTest;
	QTest::qExec(&filterTest);

	ClubFrontendTest::MemberDialogTest dialogTest;
	QTest::qExec(&dialogTest);

	ClubFrontendTest::MainWindowTest mainWindowTest;
	QTest::qExec(&mainWindowTest);

	return 0;
}
