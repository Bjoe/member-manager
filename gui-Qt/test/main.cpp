#include "memberdialogtest.h"

#include <QtTest/QtTest>

int main(int argc, char* argv[])
{

//   IClubMemberTest memberTest;
//   QTest::qExec(&memberTest);

   QApplication app(argc, argv);
   ClubFrontendTest::MemberDialogTest dialogTest;
   QTest::qExec(&dialogTest);

   return 0;
}

