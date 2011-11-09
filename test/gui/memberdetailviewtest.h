#ifndef MEMBERDETAILVIEWTEST_H
#define MEMBERDETAILVIEWTEST_H

#include <QtTest/QtTest>
#include "testcoverageobject.h"
#include "database/databaseutil.h"

namespace membermanagertest
{
namespace gui
{

class MemberDetailViewTest : public qttestutil::TestCoverageObject
{
    Q_OBJECT

public:
    MemberDetailViewTest();

private slots:
    void initTestCase();
    void initTest();
    void testShowMember();
    void testChangeMember();
    void testChangeMemberWithNewContribution();
    void testgetSaldo();
    void testgetContribution();

private:
    qttestutil::database::DatabaseUtil database;
};

}
}

#endif // MEMBERDETAILVIEWTEST_H
