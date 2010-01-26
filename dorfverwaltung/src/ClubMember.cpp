//           mitglied.cpp
//  Fri Apr  3 07:35:05 2009
//  Copyright  2009  joerg
//  <joerg@<host>>

#include "ClubMember.hpp"

namespace ClubBackend
{

    ClubMember::ClubMember(const MemberManagement::DorfManagement& aDatabase) : member(aDatabase)
    {
    }

    ClubMember::ClubMember(const litesql::Database& aDatabase, const litesql::Record& aRecord) : member(aDatabase,aRecord)
    {
    }

    void ClubMember::setEntryDate(const boost::gregorian::date& anEntryDate)
    {
        litesql::Date sqlDate(anEntryDate.day(),anEntryDate.month(),anEntryDate.year());
        member.dateOfEntry = sqlDate;
    }

    boost::gregorian::date ClubMember::getEntryDate() const
    {
        litesql::Date sqlDate = member.dateOfEntry;
        return boost::gregorian::date(sqlDate.year(),sqlDate.month(),sqlDate.day());
    }

    void ClubMember::setLeavingDate(const boost::gregorian::date& anLeavingDate)
    {
        litesql::Date sqlDate(anLeavingDate.day(),anLeavingDate.month(),anLeavingDate.year());
        member.dateOfEntry = sqlDate;
    }

    boost::gregorian::date ClubMember::getLeavingDate() const
    {
        litesql::Date sqlDate = member.dateOfEntry;
        return boost::gregorian::date(sqlDate.year(),sqlDate.month(),sqlDate.day());
    }

    void ClubMember::setEmail(const EMail::EMail& anEmailAdr)
    {
        member.email = anEmailAdr.getAddress();
    }

    EMail::EMail ClubMember::getEmail() const
    {
        return EMail::EMail(member.email);
    }
}
