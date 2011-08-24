#ifndef CONNECTIONDIALOGTEST_H_
#define CONNECTIONDIALOGTEST_H_

#include <QtTest/QtTest>

namespace ClubFrontendTest
{
namespace Gui
{

class ConnectionDialogTest: public QObject
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
