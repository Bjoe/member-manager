#ifndef MEMBERDAOTEST_H
#define MEMBERDAOTEST_H

#include <QtTest/QtTest>
#include "testcoverageobject.h"

namespace membermanagertest
{
namespace model
{

class MemberDaoTest : public qttestutil::TestCoverageObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testNewMember();
    void testGetRecordWithMemberId();
    void testGetRecordWithMemberIdWithSort();
    void testSaveRecord();
    void testDeleteMember();
};

}
}

#endif // MEMBERDAOTEST_H
