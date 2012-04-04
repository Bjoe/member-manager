#ifndef CONTRIBUTIONRECEIPTTEST_H_
#define CONTRIBUTIONRECEIPTTEST_H_

#include <QtTest/QtTest>
#include "testcoverageobject.h"

namespace membermanagertest
{

class ContributionReceiptTest : public qttestutil::TestCoverageObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testContribution();
};

}

#endif /* CONTRIBUTIONRECEIPTTEST_H_ */
