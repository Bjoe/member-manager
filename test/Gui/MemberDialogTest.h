#ifndef MEMBERDIALOGTEST_H
#define MEMBERDIALOGTEST_H

#include <QtTest/QtTest>

namespace ClubFrontendTest
{
namespace Gui
{

class MemberDialogTest: public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void showMember();
    void newMember();
    void changeMember();
    void newMemberDiscard();
    void showSaldo();
    void showfee();
};

}
}

#endif // MEMBERDIALOGTEST_H
