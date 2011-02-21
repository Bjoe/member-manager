#ifndef MAINWINDOWTEST_H
#define MAINWINDOWTEST_H

#include <QtTest/QtTest>

#include <Handler.h>

namespace ClubFrontendTest
{
namespace Gui
{

class MainWindowTest: public QObject, public TestUtils::Handler
{
    Q_OBJECT

public:
    virtual void handle();

private slots:
    void init();

    void testNewMember();
    void testEditMember();
    void testSelectedMember();
    void testMemberView();
    void testDeletedMemberView();
    void testShowKassaView();
    void testShowSaldo();

private:
    QString id;
};

}
}

#endif
