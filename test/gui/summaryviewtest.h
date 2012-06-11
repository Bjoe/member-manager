#ifndef MEMBERMANAGERTEST_GUI_SUMMARYVIEWTEST_H
#define MEMBERMANAGERTEST_GUI_SUMMARYVIEWTEST_H

#include <QtTest/QtTest>

#include "testcoverageobject.h"

namespace membermanagertest
{
namespace gui
{

class SummaryViewTest : public qttestutil::TestCoverageObject
{
    Q_OBJECT

private slots:
   void initTestCase();
   void testSummary();
};

} // namespace gui
} // namespace membermanagertest

#endif // MEMBERMANAGERTEST_GUI_SUMMARYVIEWTEST_H
