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

MemberFilter &MemberFilter::withDeleted(const bool aBoolean)
{
    QString column = MemberTable::COLUMNNAME[MemberTable::Deleted];
    QString deletedColumn(column + "='false'");
    if (aBoolean) {
        deletedColumn = column + "='true'";
    }
    columns.append(deletedColumn);
    return *this;
}

QString MemberFilter::createFilter() const
{
    return columns.join(" AND ");
}

}
}
