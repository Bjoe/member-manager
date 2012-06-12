#ifndef MEMBERDAOTEST_H
#define MEMBERDAOTEST_H

#include <QtTest/QtTest>
#include "testcoverageobject.h"

namespace membermanagertest
{
namespace dao
{

class MemberDaoTest : public qttestutil::TestCoverageObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testFindByMemberId();
    void testFindByDeleted();
    void testSelectDeleted();
    void testNewMember();
    void testSaveRecord();
    void testDeleteMember();
};

}
}

#endif // MEMBERDAOTEST_H
