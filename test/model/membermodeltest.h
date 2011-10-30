#ifndef MEMBERMODELTEST_H_
#define MEMBERMODELTEST_H_

#include <QtTest/QtTest>
#include "testcoverageobject.h"

namespace membermanagertest
{
namespace model
{

class MemberModelTest: public qttestutil::TestCoverageObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testGetLastError();
    void testGetMemberModel();
    void testSetFilter();
    void testGetMemberId();
};

}
}

#endif /* MEMBERMODELTEST_H_ */
