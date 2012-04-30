#ifndef MEMBERMANAGERTEST_DAO_CONTRIBUTIONDAOTEST_H
#define MEMBERMANAGERTEST_DAO_CONTRIBUTIONDAOTEST_H

#include <QtTest/QtTest>
#include "testcoverageobject.h"

namespace membermanagertest {
namespace dao {

class ContributionDaoTest : public qttestutil::TestCoverageObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testSaveNewRecord();
    void testSaveRecord();
    void testFindByMemberIdWithPointInTime();
    void testFindLastDateByMemberId();
    void testGetModelByMemberId();
    void testInsertNewEmptyRowAndDeletRow();
};

} // namespace model
} // namespace membermanagertest

#endif // MEMBERMANAGERTEST_DAO_CONTRIBUTIONDAOTEST_H
