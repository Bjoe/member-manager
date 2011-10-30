#ifndef DEBITSUMSUMMARYTEST_H
#define DEBITSUMSUMMARYTEST_H

#include <QtTest/QtTest>
#include "testcoverageobject.h"

namespace membermanagertest
{

class DebitSumSummaryTest : public qttestutil::TestCoverageObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testDebitSum();
};

}

#endif // DEBITSUMSUMMARYTEST_H
