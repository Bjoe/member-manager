#include "model/memberfilter.h"
#include "model/databasestructure.h"

namespace membermanager
{
namespace model
{

MemberFilter::MemberFilter() :
    columns()
{}

MemberFilter MemberFilter::build()
{
    MemberFilter memberFilter;
    return memberFilter;
}

MemberFilter &MemberFilter::withDeleted(bool isDeleted)
{
    QString result;
    if (isDeleted)
        result = QString("'true'");
    else
        result = QString("'false'");

    QString column = MemberTable::COLUMNNAME[MemberTable::Deleted];
    QString deletedColumn = QString(column + " = %1").arg(result);
    columns.append(deletedColumn);
    return *this;
}

MemberFilter &MemberFilter::withMemberId(int anId)
{
    /// \todo wrong table ?
    QString columname = ContributionTable::COLUMNNAME[ContributionTable::MemberId];
    QString memberIdColumn = QString(columname + " = %1").arg(anId);
    columns.append(memberIdColumn);
    return *this;
}

QString MemberFilter::createFilter() const
{
    return columns.join(" AND ");
}

}
}
