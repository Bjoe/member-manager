/*
 * MemberFilter.cpp
 *
 *  Created on: Jul 6, 2010
 *      Author: joerg
 */

#include "Model/MemberFilter.h"
#include "Model/DatabaseStructure.h"

namespace ClubFrontend
{

void MemberFilter::setDeleted ( const bool aBoolean )
{
    QString column = MemberTable::COLUMNNAME[MemberTable::Deleted];
    QString deletedColumn ( column + "='false'" );
    if ( aBoolean )
    {
        deletedColumn = column + "='true'";
    }
    columns.append ( deletedColumn );
}

QString MemberFilter::getFilter() const
{
    return columns.join ( " AND " );
}

}
