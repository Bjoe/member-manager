#include "Balance.hpp"

namespace ClubBackend
{

Balance::Balance(const MemberManagement::DorfManagement& aDatabase) : balance(aDatabase)
{
	//ctor
}

Balance::Balance(const litesql::Database& aDatabase, const litesql::Record& aRecord) : balance(aDatabase, aRecord)
{
}

void Balance::setDate(const boost::gregorian::date& aDate)
{
	litesql::Date sqlDate(aDate.day(), aDate.month(), aDate.year());
	balance.date = sqlDate;
}

boost::gregorian::date Balance::getDate() const
{
	litesql::Date sqlDate = balance.date;
	return boost::gregorian::date(sqlDate.year(),sqlDate.month(),sqlDate.day());
}

}
