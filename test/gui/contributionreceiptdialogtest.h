#ifndef MEMBERMANAGERTEST_GUI_CONTRIBUTIONRECEIPTDIALOGTEST_H
#define MEMBERMANAGERTEST_GUI_CONTRIBUTIONRECEIPTDIALOGTEST_H

#include <QtTest/QtTest>

#include "testcoverageobject.h"

namespace membermanagertest
{
namespace gui
{

class ContributionReceiptDialogTest : public qttestutil::TestCoverageObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testShowDialog();
};

} // namespace gui
} // namespace membermanagertest

#endif // MEMBERMANAGERTEST_GUI_CONTRIBUTIONRECEIPTDIALOGTEST_H
