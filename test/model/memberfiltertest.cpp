#include "memberfiltertest.h"

#include "model/memberfilter.h"

#include <QString>

namespace membermanagertest
{
namespace model
{

void MemberFilterTest::testSetDeleted()
{
    using membermanager::model::MemberFilter;
    QString filter = MemberFilter::build().withDeleted(true).createFilter();

    QCOMPARE(filter, QString("deleted = 'true'"));
}

void MemberFilterTest::testSetDeletedFalse()
{
    using membermanager::model::MemberFilter;
    QString filter = MemberFilter::build().withDeleted(false).createFilter();

    QCOMPARE(filter, QString("deleted = 'false'"));
}

void MemberFilterTest::testSetMemberId()
{
    using membermanager::model::MemberFilter;
    QString filter = MemberFilter::build().withMemberId(23).createFilter();

    QCOMPARE(filter, QString("dorfmitglied_pkey = 23"));
}

}
}

QTEST_MAIN(membermanagertest::model::MemberFilterTest)
#include "memberfiltertest.moc"
