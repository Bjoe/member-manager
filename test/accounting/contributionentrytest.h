#ifndef MEMBERMANAGERTEST_ACCOUNTING_CONTRIBUTIONENTRYTEST_H
#define MEMBERMANAGERTEST_ACCOUNTING_CONTRIBUTIONENTRYTEST_H

#include <QtTest/QtTest>
#include "testcoverageobject.h"

namespace membermanagertest {
namespace accounting {

class ContributionEntryTest : public qttestutil::TestCoverageObject
{
    Q_OBJECT

private slots:
    void testCreateEntry();
};

} // namespace accounting
} // namespace membermanagertest

#endif // MEMBERMANAGERTEST_ACCOUNTING_CONTRIBUTIONENTRYTEST_H
