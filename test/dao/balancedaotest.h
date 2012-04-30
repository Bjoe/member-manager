#ifndef BALANCEDAOTEST_H
#define BALANCEDAOTEST_H

#include <QtTest/QtTest>
#include "testcoverageobject.h"

namespace membermanagertest
{
namespace dao
{

class BalanceDaoTest : public qttestutil::TestCoverageObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testSaveBalance();
    void testGetMemberBalance();
    void testGetModelByMemberId();
    void testInsertNewEmptyRowAndDeletRow();
};

}
}

#endif // BALANCEDAOTEST_H
