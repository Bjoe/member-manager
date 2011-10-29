#include "memberfiltertest.h"

#include "model/memberfilter.h"

#include <QString>

namespace membermanagertest
{
namespace model
{

void MemberFilterTest::testSetDeleted()
{
    membermanager::model::MemberFilter filter;
    filter.setDeleted(true);

    QCOMPARE(filter.getFilter(), QString("deleted='true'"));
}

void MemberFilterTest::testSetDeletedFalse()
{
    membermanager::model::MemberFilter filter;
    filter.setDeleted(false);

    QCOMPARE(filter.getFilter(), QString("deleted='false'"));
}

}
}

QTEST_MAIN(membermanagertest::model::MemberFilterTest)
#include "memberfiltertest.moc"
