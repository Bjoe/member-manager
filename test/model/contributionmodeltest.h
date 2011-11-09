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
    void testGetMemberId();
    void testInsertAndDeleteRow();
};

}
}

#endif // CONTRIBUTIONMODELTEST_H
