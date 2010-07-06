#include "MemberModelTest.h"
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

	ClubFrontendTest::MemberDialogTest dialogTest;
	QTest::qExec(&dialogTest);

	ClubFrontendTest::MainWindowTest mainWindowTest;
	QTest::qExec(&mainWindowTest);

	return 0;
}
