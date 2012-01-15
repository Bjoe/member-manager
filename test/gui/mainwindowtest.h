#ifndef MAINWINDOWTEST_H
#define MAINWINDOWTEST_H

#include <QtTest/QtTest>
#include "testcoverageobject.h"

namespace membermanagertest
{
namespace gui
{

class MainWindowTest: public qttestutil::TestCoverageObject
{
    Q_OBJECT

private slots:
    void init();

    void testNewMember();
    void testSelectedMember();
    void testMemberView();
    void testDeletedMemberView();
};

}
}

#endif
