#ifndef COUNTMEMBERSUMMARYTEST_H
#define COUNTMEMBERSUMMARYTEST_H

#include <QtTest/QtTest>
#include "testcoverageobject.h"

namespace membermanagertest
{

class CountMemberSummaryTest : public qttestutil::TestCoverageObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testCountMember();
};

}

#endif // COUNTMEMBERSUMMARYTEST_H
