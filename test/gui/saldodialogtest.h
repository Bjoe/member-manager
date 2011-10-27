#ifndef SALDODIALOGTEST_H
#define SALDODIALOGTEST_H

#include <QtTest/QtTest>

namespace ClubFrontendTest
{
namespace Gui
{

class SaldoDialogTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testShowNothing();
    void testShowDialog();
    void testShowSum();
};

}
}

#endif // SALDODIALOGTEST_H
