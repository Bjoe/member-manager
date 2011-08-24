#ifndef MAINWINDOWTEST_H
#define MAINWINDOWTEST_H

#include <QtTest/QtTest>

#include "handler.h"

namespace ClubFrontendTest
{
namespace Gui
{

class MainWindowTest: public QObject, public qttestutil::Handler
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
    void testShowSaldo();

private:
    QString id;
};

}
}

#endif
