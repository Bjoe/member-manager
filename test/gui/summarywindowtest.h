#ifndef SUMMARYWINDOWTEST_H
#define SUMMARYWINDOWTEST_H

#include <QtTest/QtTest>
#include "testcoverageobject.h"

namespace membermanagertest
{
namespace gui
{

class SummaryWindowTest : public qttestutil::TestCoverageObject
{
    Q_OBJECT

private slots:
    void testShowSummary();
};

}
}

#endif // SUMMARYWINDOWTEST_H
