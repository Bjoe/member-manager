#ifndef MEMBERCONTRIBUTIONTEST_H
#define MEMBERCONTRIBUTIONTEST_H

#include <QtTest/QtTest>
#include "testcoverageobject.h"

namespace membermanagertest
{

class MemberContributionTest : public qttestutil::TestCoverageObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testGetContribution();
    void testSaveContribution();
    void testSaveNewContribution();

};

}

#endif // MEMBERCONTRIBUTIONTEST_H
