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

public:
    SummaryWindowTest();

public slots:
    void buttonClicked();

private:
    bool isClicked;

private slots:
    void testShowSummary();
    void testAddButton();
};

}
}

#endif // SUMMARYWINDOWTEST_H
