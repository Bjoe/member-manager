#ifndef CASHSUMSUMMARYTEST_H
#define CASHSUMSUMMARYTEST_H

#include <QtTest/QtTest>

namespace membermanagertest
{

class CashSumSummaryTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testCashSum();
};

}

#endif // CASHSUMSUMMARYTEST_H
