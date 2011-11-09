#ifndef MAINWINDOWTEST_H
#define MAINWINDOWTEST_H

#include <QtTest/QtTest>
#include "testcoverageobject.h"
#include "handler.h"

namespace membermanagertest
{
namespace gui
{

class MainWindowTest: public qttestutil::TestCoverageObject, public qttestutil::Handler
{
    Q_OBJECT

public:
    virtual void handle();

private slots:
    void init();

    void testNewMember();
    void testSelectedMember();
    void testMemberView();
    void testDeletedMemberView();
    void testShowSaldoDialog();
    void testShowContributionDialog();

private:
    QString id;
};

}
}

#endif
