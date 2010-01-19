#include "Contribution.hpp"

namespace Dorfverwaltung
{

    Contribution::Contribution(const MemberManagement::DorfManagement& aDatabase) : contribution(aDatabase)
    {
        //ctor
    }

    Contribution::Contribution(const litesql::Database& aDatabase, const litesql::Record& aRecord) : contribution(aDatabase,aRecord)
    {
    }

    void Contribution::setValidFrom(const boost::gregorian::date& aDate)
    {
        litesql::Date sqlDate(aDate.day(),aDate.month(),aDate.year());
        contribution.validFrom = sqlDate;
    }

    boost::gregorian::date Contribution::getValidFrom() const
    {
        litesql::Date sqlDate = contribution.validFrom;
        return boost::gregorian::date(sqlDate.year(),sqlDate.month(),sqlDate.day());
    }
}
