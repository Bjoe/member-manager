#include "Model/MemberDao.h"
#include "Model/DatabaseStructure.h"

namespace ClubFrontend
{
namespace Model
{

void MemberDao::deleteMember(int anId)
{
    const QString whereClause = QString ( " where %1=%2" ).arg (
                                    MemberTable::COLUMNNAME[MemberTable::MemberId] ).arg ( anId );
    const QString columnDeteled = MemberTable::COLUMNNAME[MemberTable::Deleted];

    QSqlQuery query ( "select * from " + MemberTable::TABLENAME + whereClause
                      + " AND " + columnDeteled + "='false'" );
    if ( query.next() )
    {
        query .exec ( "update " + MemberTable::TABLENAME + " set "
                      + columnDeteled + "='true' " + whereClause + " AND "
                      + columnDeteled + "='false'" );
    }
    else
    {
        query.exec ( "delete from " + MemberTable::TABLENAME + whereClause );
        query.exec ( "delete from " + AddressTable::TABLENAME + whereClause );
        query.exec ( "delete from " + BankAccountTable::TABLENAME + whereClause );
        query.exec ( "delete from " + ContributionTable::TABLENAME + whereClause
                     + " AND " + ContributionTable::COLUMNNAME[ContributionTable::Fee] + " isNull AND " +
                     ContributionTable::COLUMNNAME[ContributionTable::Donation] + " isNull AND " +
                     ContributionTable::COLUMNNAME[ContributionTable::ValidFrom] + " isNull AND" +
                     ContributionTable::COLUMNNAME[ContributionTable::Info] + " isNull" );
        query.exec ( "delete from " + RessourcenTable::TABLENAME + whereClause );
    }

}

}
}
