#ifndef SALDODIALOGTEST_H
#define SALDODIALOGTEST_H

#include <QtTest/QtTest>
#include "testcoverageobject.h"

namespace membermanagertest
{
namespace gui
{

class SaldoDialogTest : public qttestutil::TestCoverageObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testShowDialog();
    void testShowSum();
};

}
}

#endif // SALDODIALOGTEST_H
