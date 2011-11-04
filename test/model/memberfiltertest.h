#ifndef MEMBERFILTERTEST_H_
#define MEMBERFILTERTEST_H_

#include <QtTest/QtTest>
#include "testcoverageobject.h"

namespace membermanagertest
{
namespace model
{

class MemberFilterTest: public qttestutil::TestCoverageObject
{
    Q_OBJECT

private slots:
    void testSetDeleted();
    void testSetDeletedFalse();
    void testSetMemberId();
};

}
}

#endif /* MEMBERFILTERTEST_H_ */
