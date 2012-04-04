#ifndef BALANCEDAOTEST_H
#define BALANCEDAOTEST_H

#include <QtTest/QtTest>
#include "testcoverageobject.h"

namespace membermanagertest
{
namespace model
{

class BalanceDaoTest : public qttestutil::TestCoverageObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testSaveBalance();
};

}
}

#endif // BALANCEDAOTEST_H
