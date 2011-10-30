#ifndef CASHSUMSUMMARYTEST_H
#define CASHSUMSUMMARYTEST_H

#include <QtTest/QtTest>
#include "testcoverageobject.h"

namespace membermanagertest
{

class CashSumSummaryTest : public qttestutil::TestCoverageObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testCashSum();
};

}

#endif // CASHSUMSUMMARYTEST_H
