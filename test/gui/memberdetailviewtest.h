#ifndef MEMBERDETAILVIEWTEST_H
#define MEMBERDETAILVIEWTEST_H

#include <QtTest/QtTest>
#include "testcoverageobject.h"
#include "handler.h"
#include "database/databaseutil.h"

namespace membermanagertest
{
namespace gui
{

class MemberDetailViewTest : public qttestutil::TestCoverageObject, public qttestutil::Handler
{
    Q_OBJECT

public:
    MemberDetailViewTest();

public:
    virtual void handle();

private slots:
    void initTestCase();
    void initTest();
    void testShowMember();
    void testChangeMember();
    void testChangeMemberWithNewContribution();
    void testShowSaldoDialog();
    void testShowContributionDialog();

private:
    QString id;
    qttestutil::database::DatabaseUtil database;
};

}
}

#endif // MEMBERDETAILVIEWTEST_H
