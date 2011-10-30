#ifndef CONTRIBUTIONMODELTEST_H
#define CONTRIBUTIONMODELTEST_H

#include <QtTest/QtTest>
#include "testcoverageobject.h"

namespace membermanagertest
{
namespace model
{

class ContributionModelTest : public qttestutil::TestCoverageObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testModel();
    void testGetColumns();
    void testChangeInfo();
    void testNewFeeDonation();
    void testNewMemberId();
};

}
}

#endif // CONTRIBUTIONMODELTEST_H
