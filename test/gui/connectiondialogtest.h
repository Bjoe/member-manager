#ifndef CONNECTIONDIALOGTEST_H_
#define CONNECTIONDIALOGTEST_H_

#include <QtTest/QtTest>
#include "testcoverageobject.h"

namespace membermanagertest
{
namespace gui
{

class ConnectionDialogTest: public qttestutil::TestCoverageObject
{
    Q_OBJECT

private slots:
    void testGetUsername();
    void testGetPassword();
    void testGetDatebaseName();
    void testGetHostname();
    void testGetPort();
    void testGetDriverName();
    void testSetDriverName();
    void testSetWrongDriverName();
    void testOkButton();
    void testCancelButton();
};

}
}

#endif /* CONNECTIONDIALOGTEST_H_ */
