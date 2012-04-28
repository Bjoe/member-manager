#ifndef MEMBERMANAGERTEST_GUI_BALANCEDIALOGTEST_H
#define MEMBERMANAGERTEST_GUI_BALANCEDIALOGTEST_H

#include <QtTest/QtTest>
#include "testcoverageobject.h"

namespace membermanagertest
{
namespace gui
{

class BalanceDialogTest : public qttestutil::TestCoverageObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testShowDialog();
    void testWindowTitle();
    void testShowSum();
    void testInsertAndDeleteRow();
};

} // namespace gui
} // namespace membermanagertest

#endif // MEMBERMANAGERTEST_GUI_BALANCEDIALOGTEST_H
