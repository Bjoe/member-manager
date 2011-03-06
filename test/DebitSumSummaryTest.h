#ifndef DEBITSUMSUMMARYTEST_H
#define DEBITSUMSUMMARYTEST_H

#include <QtTest/QtTest>

namespace ClubFrontendTest
{

class DebitSumSummaryTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testDebitSum();
};

}

#endif // DEBITSUMSUMMARYTEST_H
