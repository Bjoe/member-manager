#include "MemberDialogTest.h"
#include "MainWindowTest.h"

#include <QtTest/QtTest>

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	ClubFrontendTest::MemberDialogTest dialogTest;
	QTest::qExec(&dialogTest);

	ClubFrontendTest::MainWindowTest mainWindowTest;
	QTest::qExec(&mainWindowTest);

	return 0;
}
