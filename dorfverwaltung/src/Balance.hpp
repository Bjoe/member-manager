#ifndef BALANCE_H
#define BALANCE_H

#include <string>
#include <vector>
#include <boost/date_time/gregorian/gregorian.hpp>

#include "dorfmanagement.hpp"

namespace Dorfverwaltung
{
    class Balance
    {
    public:
        Balance(const MemberManagement::DorfManagement& aDatabase);
        // Wird von litesql::select benoetigt
        Balance(const litesql::Database& aDatabase, const litesql::Record& aRecord);

        // Wird von litesql::select benoetigt
        static void getFieldTypes(std::vector<litesql::FieldType>& aFtypes)
        {
            MemberManagement::Balance::getFieldTypes(aFtypes);
        }

        void setAmount(const int& anAmount)
        {
            balance.amount = anAmount;
        }

        int getAmount() const
        {
            return balance.amount;
        }

        void setDescription(const std::string& aText)
        {
            balance.description = aText;
        }

        std::string getDescription() const
        {
            return balance.description;
        }

        void setInfo(const std::string& aText)
        {
            balance.info = aText;
        }

        std::string getInfo() const
        {
            return balance.info;
        }

        void setDate(const boost::gregorian::date& aDate);
        boost::gregorian::date getDate() const;

    protected:
    private:
        MemberManagement::Balance balance;
    };
}
#endif // BALANCE_H
