#include "memberdialogtest.h"
#include "mainwindowtest.h"

#include <QtTest/QtTest>
#include <gmock/gmock.h>

int main(int argc, char* argv[])
{
	::testing::GTEST_FLAG(throw_on_failure) = true;
	::testing::InitGoogleMock(&argc, argv);

	QApplication app(argc, argv);
	ClubFrontendTest::MemberDialogTest dialogTest;
	QTest::qExec(&dialogTest);

	ClubFrontendTest::MainWindowTest mainWindowTest;
	QTest::qExec(&mainWindowTest);

	return 0;
}
