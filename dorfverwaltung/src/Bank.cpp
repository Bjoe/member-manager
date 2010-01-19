#include "Bank.hpp"

namespace Dorfverwaltung
{

    Bank::Bank(const MemberManagement::DorfManagement& aDatabase) : bankAccount(aDatabase)
    {
        //ctor
    }

    Bank::Bank(const litesql::Database& aDatabase, const litesql::Record& aRecord) : bankAccount(aDatabase,aRecord)
    {
    }
}
