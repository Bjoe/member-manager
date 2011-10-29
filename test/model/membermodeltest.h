#ifndef MEMBERMODELTEST_H_
#define MEMBERMODELTEST_H_

#include <QtTest/QtTest>

namespace membermanagertest
{
namespace model
{

class MemberModelTest: public QObject
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
