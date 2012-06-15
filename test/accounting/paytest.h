#ifndef MEMBERMANAGERTEST_ACCOUNTING_PAYTEST_H
#define MEMBERMANAGERTEST_ACCOUNTING_PAYTEST_H

#include <QtTest/QtTest>
#include <testcoverageobject.h>

namespace membermanagertest {
namespace accounting {

class PayTest : public qttestutil::TestCoverageObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testPay();
    void testAdditionalPay();
    void testPayWithoutBooking();
    void testPaySum();
};

} // namespace accounting
} // namespace membermanagertest

#endif // MEMBERMANAGERTEST_ACCOUNTING_PAYTEST_H
