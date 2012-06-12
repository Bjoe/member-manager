#ifndef MEMBERMANAGERTEST_GUI_MEMBERDEBTVIEWTEST_H
#define MEMBERMANAGERTEST_GUI_MEMBERDEBTVIEWTEST_H

#include <QtTest/QtTest>
#include "testcoverageobject.h"

namespace membermanagertest
{
namespace gui
{

class MemberDebtViewTest : public qttestutil::TestCoverageObject
{
    Q_OBJECT
private slots:
    void initTestCase();
    void testCalculate();
};

} // namespace gui
} // namespace membermanagertest

#endif // MEMBERMANAGERTEST_GUI_MEMBERDEBTVIEWTEST_H
