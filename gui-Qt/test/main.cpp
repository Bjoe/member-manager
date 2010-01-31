#include "memberdialogtest.h"

#include <QtTest/QtTest>
#include <gmock/gmock.h>

int main(int argc, char* argv[])
{
	::testing::GTEST_FLAG(throw_on_failure) = true;
	::testing::InitGoogleMock(&argc, argv);

//   IClubMemberTest memberTest;
//   QTest::qExec(&memberTest);

	QApplication app(argc, argv);
	ClubFrontendTest::MemberDialogTest dialogTest;
	QTest::qExec(&dialogTest);

	return 0;
}
