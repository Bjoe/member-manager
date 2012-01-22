#ifndef MEMBERFACTORYTEST_H
#define MEMBERFACTORYTEST_H

#include <QtTest/QtTest>
#include "testcoverageobject.h"

namespace membermanagertest
{

class MemberFactoryTest : public qttestutil::TestCoverageObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testCreateNewMember();
    void testCreateExistsMember();
    void testCreateMemberList();
};

}

#endif // MEMBERFACTORYTEST_H
