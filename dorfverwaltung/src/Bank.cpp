#include "Bank.hpp"

namespace ClubBackend
{

    Bank::Bank(const MemberManagement::DorfManagement& aDatabase) : bankAccount(aDatabase)
    {
        //ctor
    }

    Bank::Bank(const litesql::Database& aDatabase, const litesql::Record& aRecord) : bankAccount(aDatabase,aRecord)
    {
    }
}
