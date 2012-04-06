#ifndef MEMBERTEST_H
#define MEMBERTEST_H

#include <QtTest/QtTest>
#include "testcoverageobject.h"

namespace membermanagertest
{

class MemberTest : public qttestutil::TestCoverageObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testGetMember();
    void testGetSaldoModel();
    void testGetContributionModel();
    void testSaveMember();
};

}

#endif // MEMBERTEST_H

