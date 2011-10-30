#ifndef CONTRIBUTIONDIALOGTEST_H
#define CONTRIBUTIONDIALOGTEST_H

#include <QtTest/QtTest>
#include "testcoverageobject.h"

namespace membermanagertest
{
namespace gui
{

class ContributionDialogTest : public qttestutil::TestCoverageObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testShowDialog();
};

}
}

#endif // CONTRIBUTIONDIALOGTEST_H
