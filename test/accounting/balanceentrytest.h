#ifndef BALANCEENTRYTEST_H
#define BALANCEENTRYTEST_H

#include <QtTest/QtTest>
#include <testcoverageobject.h>

namespace membermanagertest
{
namespace accounting
{

class BalanceEntryTest : public qttestutil::TestCoverageObject
{
    Q_OBJECT

private slots:
    void testCreateEntry();
};

}
}

#endif // BALANCEENTRYTEST_H
