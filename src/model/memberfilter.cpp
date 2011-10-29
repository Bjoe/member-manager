#include "model/memberfilter.h"
#include "model/databasestructure.h"

namespace membermanager
{
namespace model
{

void MemberFilter::setDeleted(const bool aBoolean)
{
    QString column = MemberTable::COLUMNNAME[MemberTable::Deleted];
    QString deletedColumn(column + "='false'");
    if (aBoolean) {
        deletedColumn = column + "='true'";
    }
    columns.append(deletedColumn);
}

QString MemberFilter::getFilter() const
{
    return columns.join(" AND ");
}

}
}
