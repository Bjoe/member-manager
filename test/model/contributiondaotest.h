#ifndef MEMBERMANAGERTEST_MODEL_CONTRIBUTIONDAOTEST_H
#define MEMBERMANAGERTEST_MODEL_CONTRIBUTIONDAOTEST_H

#include <QtTest/QtTest>
#include "testcoverageobject.h"

namespace membermanagertest {
namespace model {

class ContributionDaoTest : public qttestutil::TestCoverageObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testSaveDao();
};

} // namespace model
} // namespace membermanagertest

#endif // MEMBERMANAGERTEST_MODEL_CONTRIBUTIONDAOTEST_H
